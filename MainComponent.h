#pragma once

#include <JuceHeader.h>
#include "GUIPlayer.h"
#include "PlaylistComponent.h"

class MainComponent : public juce::AudioAppComponent
{
public:

    MainComponent();
    ~MainComponent() override;

    void resized() override;
    void prepareToPlay(int SamplesPerBlockExpected, double SampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void activateSecondPlayer();  // To active player2 .
    void onTrackLoaded(const juce::File& newFile);
    void updateMetadataFromPlayer(clsAudioPlayer& player);// To update metadata display
    void paint(juce::Graphics& g) override;// To print program name
   
private:
    bool IsOne = true;
    juce::TextButton AddButton;
    juce::TextButton DeleteButton;
    clsGUIPlayer Player1;
    clsGUIPlayer Player2;
    juce::MixerAudioSource mixer;
    bool isSecondPlayerActive = false;
    juce::File lastLoadedFile;

    clsPlaylistComponent playlist;
  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};