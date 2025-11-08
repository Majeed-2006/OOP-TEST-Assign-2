#include "MainComponent.h"

MainComponent::MainComponent()
    : playlist(Player1.getAudioPlayer(), Player2.getAudioPlayer())
{

    addAndMakeVisible(Player1);
    addAndMakeVisible(Player2);
    Player2.setVisible(false);

    AddButton.setButtonText("Add Player");
    addAndMakeVisible(AddButton);
    DeleteButton.setButtonText("Delete Player");
    addAndMakeVisible(DeleteButton);
    DeleteButton.setVisible(false);

    AddButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgrey);
    AddButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    DeleteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    DeleteButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);

    AddButton.onClick = [this]()
        {
            Player2.setVisible(true);
            AddButton.setVisible(false);
            DeleteButton.setVisible(true);
            IsOne = !IsOne;
        };
    DeleteButton.onClick = [this]()
        {
            Player2.setVisible(false);
            DeleteButton.setVisible(false);
            AddButton.setVisible(true);
            IsOne = !IsOne;
        };

    addAndMakeVisible(playlist);
    addAndMakeVisible(playlist.addToPlaylistButton);

    setSize(500, 300);


    mixer.addInputSource(&Player1, false);
    mixer.addInputSource(&Player2, false);
    setAudioChannels(0, 2);

    Player1.setOnFileLoadedCallback([this](juce::File newFile)
        {
            if (lastLoadedFile != juce::File() && newFile != lastLoadedFile)
                activateSecondPlayer();

            lastLoadedFile = newFile;
        });

}

MainComponent::~MainComponent()
{
    mixer.removeAllInputs();
    shutdownAudio();
}


void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
//audio
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixer.getNextAudioBlock(bufferToFill);
}
//audio
void MainComponent::releaseResources()
{

    mixer.releaseResources();

}


void MainComponent::activateSecondPlayer()
{
    if (!isSecondPlayerActive)
    {
        isSecondPlayerActive = true;
        Player2.setVisible(true);
        resized();
    }
}
void MainComponent::onTrackLoaded(const juce::File& newFile)
{
    if (lastLoadedFile != juce::File())
    {
        if (newFile != lastLoadedFile)
        {
            activateSecondPlayer();
        }
    }

    lastLoadedFile = newFile;
}

void MainComponent::updateMetadataFromPlayer(clsAudioPlayer& player)
{
    if (&player == &Player1.getAudioPlayer())
        Player1.syncMetadataFromPlayer(player);
    else if (&player == &Player2.getAudioPlayer())
        Player2.syncMetadataFromPlayer(player);
}

void MainComponent::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    // Chooses the color of the text
    g.setColour(juce::Colours::white);

    //choose the font type
    g.setFont(juce::Font(45.0f, juce::Font::bold | juce::Font::italic));


    // A custom rectangle to precisely define the text position

    juce::Rectangle<int> textArea{ 260, 20, 400, 50 }; // x=260, y=20 width=400, height=50

    //Actually draws the text on the screen
    g.drawText("Audio Minimalizer", textArea, juce::Justification::topLeft, true);
}

void MainComponent::resized()
{
    auto area = getLocalBounds();


    int playlistWidth = 250;
    auto playlistArea = area.removeFromLeft(playlistWidth);

    playlist.setBounds(playlistArea.reduced(5));

    AddButton.setBounds(1430, 550, 100, 40);
    DeleteButton.setBounds(1430, 550, 100, 40);
    Player1.setBounds(260, 30, 1300, 395);
    Player2.setBounds(260, 490, 1300, 400);

}