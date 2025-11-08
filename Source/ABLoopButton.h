#pragma once

#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsABLoopButton : public juce::Component
{
private:
	
	juce::AudioTransportSource transportSource;

	clsAudioPlayer* AudioPlayer;

	
	

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsABLoopButton)


public:
	juce::TextButton ABLoopButton;
	
	
	clsABLoopButton(clsAudioPlayer& Player)
	{
		AudioPlayer = &Player;
		ABLoopButton.setButtonText("ABLoop");
		addAndMakeVisible(ABLoopButton);
		
		ABLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgrey); 
	
		ABLoopButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black); 
	}
		
	

	void resized()
	{
		ABLoopButton.setBounds(0, 0, getWidth(), getHeight());
	}

	void HandleClick(double StartPos, double EndPos)
	{

		ABLoopButton.setButtonText("ABLoop : ON");
		AudioPlayer->LoopAudioFromAToB(StartPos, EndPos);

	}

};