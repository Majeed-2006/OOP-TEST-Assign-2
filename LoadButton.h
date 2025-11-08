
#include <JuceHeader.h>
#include "AudioPlayer.h" 

class clsLoadButton : public juce::Component
{
private:

    //juce::AudioTransportSource transportSource;
    clsAudioPlayer* AudioPlayer;
    std::unique_ptr<juce::FileChooser> fileChooser;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsLoadButton)

public:

    juce::TextButton LoadButton;
    std::function<void(juce::File)> onFileLoaded; 

    //Audio Data after Read From Load Function
    juce::String currentFileName;
    juce::String currentFilePath;
    juce::String durationText;
    juce::String durationInSeconds;



    clsLoadButton(clsAudioPlayer& Player)
    {
        AudioPlayer = &Player;
        LoadButton.setButtonText("Load");
        addAndMakeVisible(LoadButton);
        LoadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgrey);
	
        LoadButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black); 
      

    bool HandleClick()
    {
        fileChooser = std::make_unique<juce::FileChooser>("Select an audio file...", juce::File{}, "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& chooser)
            {
                auto file = chooser.getResult();
                if (file.existsAsFile())
                {
                    AudioPlayer->LoadAudioFile(file);
                    currentFileName = AudioPlayer->currentFileName;
                    currentFilePath = AudioPlayer->currentFilePath;
                    durationInSeconds = juce::String(AudioPlayer->durationInSeconds, 2) + " s";
                    if (auto* parent = getParentComponent())
                        parent->repaint();

                    if (onFileLoaded)
                        onFileLoaded(file);

                }

            });
        return true;

    }

    void resized()
    {
        LoadButton.setBounds(getLocalBounds());
    };

};