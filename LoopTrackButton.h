#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsLoopButton : public juce::Component
{
private:
    clsAudioPlayer* AudioPlayer = nullptr;
    bool isLooping = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsLoopButton)

public:
    juce::TextButton LoopButton;
    clsLoopButton(clsAudioPlayer& player)
    {
        LoopButton.setButtonText("Loop");
        AudioPlayer = &player;
        LoopButton.setClickingTogglesState(true);
        addAndMakeVisible(LoopButton);
        LoopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgrey); 
	
        LoopButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black); 
    }
  

    void resized() 
    {
        LoopButton.setBounds(getLocalBounds());
    }

    void HandleClick()
    {
        bool shouldLoop = LoopButton.getToggleState();
        AudioPlayer->LoopingAudio(shouldLoop);

        if (shouldLoop)
            LoopButton.setButtonText("Loop: ON");
        else
            LoopButton.setButtonText("Loop");
    }

};
