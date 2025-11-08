#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsGoForwardButton : public juce::Component
{
private:
    juce::AudioTransportSource transportSource;
    clsAudioPlayer* AudioPlayer;
    std::unique_ptr<juce::Drawable> GoForwardSVG;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsGoForwardButton)
public:
    //juce::TextButton GoForwardButton;
    juce::DrawableButton GoForwardButton{ "GoForward", juce::DrawableButton::ImageRaw };
    clsGoForwardButton(clsAudioPlayer& Player)
    {
        AudioPlayer = &Player;
        GoForwardSVG = juce::Drawable::createFromImageData(
            BinaryData::GoForward_svg,
            BinaryData::GoForward_svgSize
        );

        if (GoForwardSVG != nullptr)
        {
          
	
            juce::Rectangle<float> buttonArea(0, 0, 40.0f, 40.0f);

           

            GoForwardSVG->replaceColour(juce::Colours::black, juce::Colours::lightgrey); // optional
            GoForwardSVG->setTransformToFit(buttonArea, juce::RectanglePlacement::centred);

            GoForwardButton.setImages(GoForwardSVG.get());
        }

        addAndMakeVisible(GoForwardButton);
    }



    void resized()
    {
        GoForwardButton.setBounds(getLocalBounds());
    }

    void HandleClick()
    {

        AudioPlayer->GoForward();

    }
};