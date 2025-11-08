#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsEndButton : public juce::Component
{
private:
    juce::AudioTransportSource transportSource;
    clsAudioPlayer* AudioPlayer;

    std::unique_ptr<juce::Drawable> EndSVG;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsEndButton)
public:
   //juce::TextButton EndButton;
    juce::DrawableButton EndButton{ "End", juce::DrawableButton::ImageRaw };
    clsEndButton(clsAudioPlayer& Player)
    {
        AudioPlayer = &Player;
        EndSVG = juce::Drawable::createFromImageData(BinaryData::end_svg,BinaryData::end_svgSize
        );

        if (EndSVG != nullptr)
        {

            juce::Rectangle<float> buttonArea(0, 0, 40.0f, 40.0f);

          
            EndSVG->replaceColour(juce::Colours::black, juce::Colours::lightgrey); // optional
            EndSVG->setTransformToFit(buttonArea, juce::RectanglePlacement::centred);

            EndButton.setImages(EndSVG.get());
        }
        addAndMakeVisible(EndButton);
    }
  

    
    void resized()
    {
        EndButton.setBounds(getLocalBounds());
    }

    void HandleClick()
    {
        AudioPlayer->EndAudio();
    }
};