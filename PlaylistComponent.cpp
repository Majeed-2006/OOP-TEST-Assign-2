
#include "PlaylistComponent.h"
#include "PlaylistRowComponent.h"
//#include "GUIPlayer.h"
#include "MainComponent.h"
clsPlaylistComponent::clsPlaylistComponent(clsAudioPlayer& player1Ref, clsAudioPlayer& player2Ref)
    : player1(player1Ref),
    player2(player2Ref)
{
    // Playlist header
    headerLabel.setText("Playlist", juce::dontSendNotification);
    headerLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    headerLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    headerLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(headerLabel);

    // Title header
    headerTitleLabel.setText("Track title", juce::dontSendNotification);
    headerTitleLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    headerTitleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    headerTitleLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey);
    headerTitleLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(headerTitleLabel);

    addAndMakeVisible(addToPlaylistButton);
    addToPlaylistButton.addListener(this);
    // Default target player
    addAndMakeVisible(deck1Button);
    addAndMakeVisible(deck2Button);

    // Radio button to one select
    deck1Button.setRadioGroupId(1);
    deck2Button.setRadioGroupId(1);

    deck1Button.setToggleState(true, juce::dontSendNotification);// Deck 1 Bright at first
    targetPlayer = &player1;// Default target to player 1

    deck1Button.addListener(this);
    deck2Button.addListener(this);

    addAndMakeVisible(playlistBox);
    playlistBox.setModel(this);
    playlistBox.setRowHeight(35);

}

void clsPlaylistComponent::addFile(const juce::File& file)
{
    playlistFiles.push_back(file);
    playlistBox.updateContent();
}

int clsPlaylistComponent::getNumRows()
{
    return (int)playlistFiles.size();
}

void clsPlaylistComponent::HandleClick()
{
    addToPlaylistChooser = std::make_unique<juce::FileChooser>(
        "Select Audio Files to Add to Playlist",
        juce::File{},
        "*.wav;*.mp3;*.aiff");
    addToPlaylistChooser->launchAsync(
        juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectMultipleItems,
        [this](const juce::FileChooser& chooser)
        {
            auto selectedFiles = chooser.getResults();
            for (const auto& file : selectedFiles)
            {
                addFile(file);
            }
        });
}

void clsPlaylistComponent::buttonClicked(juce::Button* button)
{
    if (button == &addToPlaylistButton)
    {
        DBG("Add button clicked!");
        HandleClick();
    }
    else if (button == &deck1Button)
    {
        targetPlayer = &player1; // Change target to 1
    }
    else if (button == &deck2Button)
    {
        targetPlayer = &player2; // Change target to 2
    }
}

void clsPlaylistComponent::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{

}
void clsPlaylistComponent::listBoxItemClicked(int row, const juce::MouseEvent&)
{
    if (row >= 0 && row < playlistFiles.size())
    {
        juce::File fileToPlay = playlistFiles[row];
        targetPlayer->LoadAudioFile(fileToPlay); // Download AudioPlayer file 
        targetPlayer->PlayAudio();
    }
}
juce::Component* clsPlaylistComponent::refreshComponentForRow(
    int rowNumber,
    bool,
    juce::Component* existingComponentToUpdate)
{
    // safety check
    if (rowNumber < 0 || rowNumber >= (int)playlistFiles.size())
        return nullptr;

    
    if (existingComponentToUpdate == nullptr)
    {
       
        auto file = playlistFiles[rowNumber];
        auto fileName = file.getFileName();

      
        auto* row = new clsPlaylistRowComponent(
            fileName,

           
            [this, file]()
            {
                targetPlayer->LoadAudioFile(file);
                targetPlayer->PlayAudio();
                if (auto* parent = getParentComponent())
                {
                    
                    if (auto* main = findParentComponentOfClass<MainComponent>())
                        main->updateMetadataFromPlayer(*targetPlayer);
                }
            },

           
            [this, rowNumber]()
            {
              
                if (rowNumber >= 0 && rowNumber < (int)playlistFiles.size())
                {
                    playlistFiles.erase(playlistFiles.begin() + rowNumber);

                    
                    playlistBox.updateContent();
                    playlistBox.deselectAllRows();
                    playlistBox.repaint();
                }
            });

        return row;
    }

   
    return existingComponentToUpdate;
}

void clsPlaylistComponent::resized()
{
    auto area = getLocalBounds().reduced(10);

    // ======= Playlist title =======
    auto titleArea = area.removeFromTop(30);
    headerLabel.setBounds(titleArea.reduced(5));

    // ===== Deck Buttons =====
    auto deckArea = area.removeFromTop(30);
    deck1Button.setBounds(deckArea.removeFromLeft(deckArea.getWidth() / 2).reduced(5));
    deck2Button.setBounds(deckArea.reduced(5));


    auto playlistArea = area.reduced(0, 5);

    //  ======= Track title ======
    auto trackTitleArea = playlistArea.removeFromTop(25);
    headerTitleLabel.setBounds(trackTitleArea.reduced(5));

    // ======= Add to playlist Button ======
    int buttonHeight = 40;
    auto addButtonArea = playlistArea.removeFromBottom(buttonHeight + 5);
    addToPlaylistButton.setBounds(addButtonArea.reduced(5));


    playlistBox.setBounds(playlistArea.reduced(5));
}

