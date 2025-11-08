#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsEchoButton : public juce::Component
{
private:
    juce::AudioTransportSource transportSource;
    clsAudioPlayer* AudioPlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsEchoButton)
public:
    juce::TextButton EchoButton;

    clsEchoButton(clsAudioPlayer& Player)
    {
        AudioPlayer = &Player;
        EchoButton.setButtonText("Echo");
       
        addAndMakeVisible(EchoButton);
    }



    void resized()
    {
        EchoButton.setBounds(0, 0, getWidth(), getHeight());
    }

    void HandleClick()
    {
        
            AudioPlayer->GoBackButton();
        
    }
};