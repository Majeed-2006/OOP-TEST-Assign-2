#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsSeekSlider : public juce::Component, public juce::Timer
{
private:
    clsAudioPlayer* AudioPlayer;
    juce::Label RemainingLabel; 
    juce::Label elapsedLabel;

public:
    juce::Slider SeekSlider;

    clsSeekSlider(clsAudioPlayer& player)
    {
        AudioPlayer = &player;

        SeekSlider.setSliderStyle(juce::Slider::LinearHorizontal);
        SeekSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        SeekSlider.setRange(0, 1, 1);
        addAndMakeVisible(SeekSlider);

        elapsedLabel.setFont(juce::Font(14.0f, juce::Font::bold));
        elapsedLabel.setJustificationType(juce::Justification::centredLeft);
        addAndMakeVisible(elapsedLabel);

        RemainingLabel.setFont(juce::Font(14.0f, juce::Font::bold));
        RemainingLabel.setJustificationType(juce::Justification::centredRight);
        addAndMakeVisible(RemainingLabel);

        updateRange();


        SeekSlider.onValueChange = [this]()
            {
                if (SeekSlider.isMouseButtonDown())
                {
                    double sec = SeekSlider.getValue();
                    AudioPlayer->SetPosition(sec);
                }
            };
        startTimer(200);
    }


    void resized() override
    {
        auto area = getLocalBounds();

        int sliderHeight = 20;
        SeekSlider.setBounds(area.removeFromTop(sliderHeight));

        int labelHeight = 20;
        int labelWidth = 60;

        elapsedLabel.setBounds(10, sliderHeight + 2, labelWidth, labelHeight);
        RemainingLabel.setBounds(getWidth() - labelWidth - 10, sliderHeight + 2, labelWidth, labelHeight);
    }

    void SliderHandel()
    {

        if (SeekSlider.isMouseButtonDown())
        {

            double sec = SeekSlider.getValue();
            AudioPlayer->SetPosition(sec);
            SeekSlider.setTextValueSuffix("  " + AudioPlayer->formatSecondsToHHMMSS(sec));
        }
    }

    
    void timerCallback() override
    {
        if (!SeekSlider.isMouseButtonDown())
        {
            double pos = AudioPlayer->GetPosition();
            SeekSlider.setValue(pos, juce::dontSendNotification);
        }

        double current = AudioPlayer->GetPosition();
        double total = AudioPlayer->GetLength();
        double remaining = total - current;

        elapsedLabel.setText(formatTime(current), juce::dontSendNotification);
        RemainingLabel.setText("-" + formatTime(remaining), juce::dontSendNotification);

        updateRange();
    }

    juce::String formatTime(double seconds)
    {
        int totalSeconds = (int)seconds;
        int minutes = totalSeconds / 60;
        int secs = totalSeconds % 60;

        return juce::String::formatted("%02d:%02d", minutes, secs);
    }


    void updateRange()
    {
        double length = AudioPlayer->GetLength(); // seconds

        if (length > 0)
            SeekSlider.setRange(0.0, (double)std::round(length), 1.0);
    }

};
