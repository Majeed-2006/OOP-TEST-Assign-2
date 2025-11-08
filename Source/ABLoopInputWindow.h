#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsABLoopInputWindow : public juce::Component
{
public:
    juce::TextEditor aBox, bBox;
    juce::TextButton okBtn, cancelBtn;
    double Start = 0.0, End = 0.0;

    clsABLoopInputWindow()
    {
       
        addAndMakeVisible(aBox);
        addAndMakeVisible(bBox);
        addAndMakeVisible(okBtn);
        addAndMakeVisible(cancelBtn);

        aBox.setText("0.0");
        bBox.setText("0.0");
        okBtn.setButtonText("OK");
        cancelBtn.setButtonText("Cancel");

      
        okBtn.onClick = [this]()
            {
                Start = aBox.getText().getDoubleValue();
                End = bBox.getText().getDoubleValue();
                close();
            };

        cancelBtn.onClick = [this]()
            {
                close();
            };

        setSize(250, 150);
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black.withAlpha(0.8f));
    }

    void resized() override
    {
        auto r = getLocalBounds().reduced(10);
        aBox.setBounds(r.removeFromTop(30));
        r.removeFromTop(10);
        bBox.setBounds(r.removeFromTop(30));
        okBtn.setBounds(getWidth() / 2 - 70, getHeight() - 35, 60, 25);
        cancelBtn.setBounds(getWidth() / 2 + 10, getHeight() - 35, 60, 25);
    }

    void ShowWindow()
    {
        setVisible(true);
        if (auto* parent = getParentComponent())
        {
            parent->addAndMakeVisible(this);
            centreWithSize(getWidth(), getHeight());
        }
        resized();
    }

    void close()
    {
        setVisible(false);
    }

    double GetStart() { return Start; }
    double GetEnd() { return End; }
};
