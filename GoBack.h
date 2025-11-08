#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsGoBackButton : public juce::Component
{
private:
    juce::AudioTransportSource transportSource;
    clsAudioPlayer* AudioPlayer;
    std::unique_ptr<juce::Drawable> GoBackSVG;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsGoBackButton)
public:
   
    juce::DrawableButton GoBackButton{ "Goback", juce::DrawableButton::ImageRaw };
    clsGoBackButton(clsAudioPlayer& Player)
    {
        AudioPlayer = &Player;
        GoBackSVG = juce::Drawable::createFromImageData(
            BinaryData::GoBack_svg,
            BinaryData::GoBack_svgSize
        );

        if (GoBackSVG != nullptr)
        {
          
            juce::Rectangle<float> buttonArea(0, 0, 40.0f, 40.0f);


            GoBackSVG->replaceColour(juce::Colours::black, juce::Colours::lightgrey); // optional
            GoBackSVG->setTransformToFit(buttonArea, juce::RectanglePlacement::centred);

            GoBackButton.setImages(GoBackSVG.get());
        }
        addAndMakeVisible(GoBackButton);
    }



    void resized()
    {
        GoBackButton.setBounds(getLocalBounds());
    }

    void HandleClick()
    {

        AudioPlayer->GoBack();

    }
};