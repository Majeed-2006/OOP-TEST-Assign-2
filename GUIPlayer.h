
#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"   // clsAudioPlayer
#include "StopButton.h"
#include "PlayButton.h"
#include "LoadButton.h"
#include "LoopTrackButton.h"
#include "MuteButton.h"
#include "WaveformDisplay.h"
#include "StartBotton.h"
#include "EndButton.h"
#include "ABLoopButton.h"
#include "ABLoopInputWindow.h"
#include "SpeedSlider.h"
#include "volumeSlider.h"
#include "GoForward.h"
#include "GoBack.h"
#include "SeekSlider.h"
class clsGUIPlayer : public juce::Component, public juce::AudioSource, public juce::Button::Listener, public juce::Slider::Listener
{

private:
    // Audio logic
    clsAudioPlayer AudioPlayer;

    bool _IsOne = false;
    double PosA, PosB;

    //Buttons Classes controle
   // clsLoadButton LoadButtonObject{ AudioPlayer };
    clsLoadButton  LoadButtonObject{ AudioPlayer };
    clsPlayButton PlayButtonObject{ AudioPlayer };
    clsStopButton StopButtonObject{ AudioPlayer };
    clsLoopButton LoopButtonObject{ AudioPlayer };
    clsStartButton StartButtonObject{ AudioPlayer };
    clsEndButton EndButtonObject{ AudioPlayer };
    clsMuteButton MuteButtonObject{ AudioPlayer };
    clsWaveformDisplay WaveformDisplayObject{ AudioPlayer };
   
    clsABLoopButton ABLoopButtonObject{ AudioPlayer };
    clsABLoopInputWindow ABLoopInpuWindow;
    clsGoBackButton GoBackButtonObject{ AudioPlayer };
    clsGoForwardButton GoForwardButtonObject{ AudioPlayer };

    //Sliders Classes Contole
    clsSpeedSlider SpeedSliderObject{ AudioPlayer };
    clsVolumeSlider volumeSliderObject{ AudioPlayer };
    clsSeekSlider SeekSliderObject{ AudioPlayer };

    // Control Of Sliders:
    void sliderValueChanged(juce::Slider* slider)
    {
        if (slider == &volumeSliderObject.VolumeSlider)
        {
            volumeSliderObject.SliderHandel();
        }
        else if (slider == &SpeedSliderObject.SpeedSlider)
        {
            SpeedSliderObject.SliderHandel();
        }
        else if (slider == &SeekSliderObject.SeekSlider)
        {
            SeekSliderObject.SliderHandel();
        }

    }

    //control Of Buttons:
    void buttonClicked(juce::Button* Object)
    {
        if (Object == &LoadButtonObject.LoadButton) {
            LoadButtonObject.HandleClick();

        }
        else if (Object == &PlayButtonObject.PlayButton)
        {
           
            PlayButtonObject.HandleClick();

            
            PlayButtonObject.setVisible(false);
            StopButtonObject.setVisible(true);
        }
        else if (Object == &StopButtonObject.StopButton)
        {
           
            StopButtonObject.HandleClick();

         
            StopButtonObject.setVisible(false);
            PlayButtonObject.setVisible(true);
        }
        
        else if (Object == &EndButtonObject.EndButton)
            EndButtonObject.HandleClick();

        else if (Object == &LoopButtonObject.LoopButton)
            LoopButtonObject.HandleClick();

        else if (Object == &MuteButtonObject.MuteButton)
        {
            // When mute toggles, set the GUI slider to the player's gain
            MuteButtonObject.SetOnToggle([this]()
                {
                    // Runs on the message thread (button clicks are on message thread)
                    volumeSliderObject.VolumeSlider.setValue((double)AudioPlayer.GetGain());
                });

            MuteButtonObject.HandleClick();

        }
      
        else if (Object == &StartButtonObject.StartButton)
            StartButtonObject.HandleClick();

        else if (Object == &ABLoopButtonObject.ABLoopButton)
        {
            if (!ABLoopInpuWindow.isVisible())
            {
                ABLoopInpuWindow.aBox.setText("0.0");
                ABLoopInpuWindow.bBox.setText("0.0");

                ABLoopInpuWindow.setSize(250, 150);
                ABLoopInpuWindow.setTopLeftPosition((getWidth() - 250) / 2, (getHeight() - 150) / 2);
                addAndMakeVisible(&ABLoopInpuWindow);

                ABLoopInpuWindow.okBtn.onClick = [this]()
                    {
                        double start = ABLoopInpuWindow.aBox.getText().getDoubleValue();
                        double end = ABLoopInpuWindow.bBox.getText().getDoubleValue();

                        if (end != 0)
                        {

                            ABLoopButtonObject.HandleClick(start, end);
                            removeChildComponent(&ABLoopInpuWindow);
                        }
                    };

            }

        }
        else if (Object == &GoBackButtonObject.GoBackButton)
        {
            GoBackButtonObject.HandleClick();
        }
        else if (Object == &GoForwardButtonObject.GoForwardButton)
        {
            GoForwardButtonObject.HandleClick();
        }


    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsGUIPlayer)
public:

   
    clsGUIPlayer()
    {
        StopButtonObject.StopButton.onClick = [this]() { StopButtonObject.HandleClick(); };

        AddAndMakeVisibleComponantes();
        AddListenerOfComponnts();
        StopButtonObject.setVisible(false); 

        LoadButtonObject.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgrey); 
        LoadButtonObject.setColour(juce::TextButton::textColourOffId, juce::Colours::black); 
        LoopButtonObject.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgrey);
        LoopButtonObject.setColour(juce::TextButton::textColourOffId, juce::Colours::black); 
        ABLoopButtonObject.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgrey); 
        ABLoopButtonObject.setColour(juce::TextButton::textColourOffId, juce::Colours::black); 


    }
    // To control Audio Player from Main Component
    clsAudioPlayer& getAudioPlayer()
    {
        return AudioPlayer;
    }

    void PrintAudioData(const juce::String& Head, const juce::String& Data, juce::Graphics& g, int Ypos)
    {
        g.setColour(juce::Colours::darkblue);
        g.setFont(juce::Font("Arial", 18.0f, juce::Font::bold));
        juce::Rectangle<int> headArea{ 11, Ypos, 130, 25 };
        g.drawText(Head, headArea, juce::Justification::left, true);


        g.setColour(juce::Colours::black);
        g.setFont(juce::Font("Arial", 17.0f, juce::Font::plain));
        juce::Rectangle<int> dataArea{ 140, Ypos, 400, 25 };
        g.drawText(Data, dataArea, juce::Justification::left, true);
    }

    void setOnFileLoadedCallback(std::function<void(juce::File)> callback)
    {
        LoadButtonObject.onFileLoaded = std::move(callback);
    }

    // paint function
    void paint(juce::Graphics& g)
    {
        int yStart = 100;

      
        g.setColour(juce::Colours::black);
        

        if (LoadButtonObject.currentFileName.isEmpty() || LoadButtonObject.currentFilePath.isEmpty() || LoadButtonObject.durationInSeconds.isEmpty())
        {
            g.setColour(juce::Colours::black);
            g.setFont(juce::Font("Arial", 22.0f, juce::Font::bold));
            
            juce::Rectangle<int> dataArea(7, 100, getWidth() - 40, 90);

            g.drawText("No file loaded", dataArea, juce::Justification::centred, true);

        }
        else
        {
            int lineHeight = 25;
            PrintAudioData("Audio Name:", LoadButtonObject.currentFileName, g, yStart);
            PrintAudioData("Audio Path:", LoadButtonObject.currentFilePath, g, yStart + lineHeight);
            PrintAudioData("Audio Time:", LoadButtonObject.durationInSeconds, g, yStart + 2 * lineHeight);
        }

    }

   
    void syncMetadataFromPlayer(const clsAudioPlayer& p)
    {
        LoadButtonObject.currentFileName = p.currentFileName;
        LoadButtonObject.currentFilePath = p.currentFilePath;
        int totalSeconds = static_cast<int>(AudioPlayer.durationInSeconds);
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;

        LoadButtonObject.durationInSeconds = juce::String::formatted("%d:%02d", minutes, seconds);
        repaint(); 
    }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
       
        AudioPlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }

    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
    {
       
        AudioPlayer.getNextAudioBlock(bufferToFill);
    }

    void releaseResources()
    {
        AudioPlayer.releaseResources();
    }


    void resized()
    {
       
        int HeightTxt = 30;
        int WidthTxt = 80;

      
        LoadButtonObject.setBounds(10, 60, WidthTxt, HeightTxt);
        LoopButtonObject.setBounds(100, 60, WidthTxt, HeightTxt);
        ABLoopButtonObject.setBounds(190, 60, WidthTxt, HeightTxt);

        
        SeekSliderObject.setBounds(1, 275, getWidth() - 120, 40);
        SpeedSliderObject.setBounds(10, 360, getWidth() - 800, 30);
        volumeSliderObject.setBounds(1180, 100, 100, 200);

       
        WaveformDisplayObject.setBounds(10, 180, getWidth() - 120, 90);

        
        int XImage = 430;
        int YImage = 310;
        int WidthImage = 40;
        int HeightImage = 40;
        int spacing = 10;

        StartButtonObject.setBounds(XImage, YImage, WidthImage, HeightImage);
        GoBackButtonObject.setBounds(XImage + (WidthImage + spacing) * 1, YImage, WidthImage, HeightImage);
        PlayButtonObject.setBounds(XImage + (WidthImage + spacing) * 2, YImage, WidthImage, HeightImage);
        StopButtonObject.setBounds(XImage + (WidthImage + spacing) * 2, YImage, WidthImage, HeightImage);
       // StopButtonObject.setBounds(XImage + (WidthImage + spacing) * 3, YImage, WidthImage, HeightImage);
        GoForwardButtonObject.setBounds(XImage + (WidthImage + spacing) * 4, YImage, WidthImage, HeightImage);
        EndButtonObject.setBounds(XImage + (WidthImage + spacing) * 5, YImage, WidthImage, HeightImage);
        MuteButtonObject.setBounds(1215, YImage, WidthImage, HeightImage);
    }


        
    
    
   

    //control of all componantes:
    void AddAndMakeVisibleComponantes()
    {
        //Buttons:
        addAndMakeVisible(LoadButtonObject);
        addAndMakeVisible(PlayButtonObject);
        addAndMakeVisible(StopButtonObject);
        addAndMakeVisible(LoopButtonObject);
        addAndMakeVisible(MuteButtonObject);
        addAndMakeVisible(StartButtonObject);
        addAndMakeVisible(EndButtonObject);
        addAndMakeVisible(ABLoopButtonObject);
        addAndMakeVisible(GoBackButtonObject);
        addAndMakeVisible(GoForwardButtonObject);
        addAndMakeVisible(SeekSliderObject);
        //sliders:
        addAndMakeVisible(WaveformDisplayObject);
        addAndMakeVisible(SpeedSliderObject);
      
        addAndMakeVisible(volumeSliderObject);

       
    }

    void AddListenerOfComponnts()
    {
        LoadButtonObject.LoadButton.addListener(this);
        PlayButtonObject.PlayButton.addListener(this);
        EndButtonObject.EndButton.addListener(this);
        LoopButtonObject.LoopButton.addListener(this);
        StopButtonObject.StopButton.addListener(this);
        StartButtonObject.StartButton.addListener(this);
        MuteButtonObject.MuteButton.addListener(this);
        ABLoopButtonObject.ABLoopButton.addListener(this);
        GoBackButtonObject.GoBackButton.addListener(this);
        GoForwardButtonObject.GoForwardButton.addListener(this);
        SeekSliderObject.SeekSlider.addListener(this);
      
        SpeedSliderObject.SpeedSlider.addListener(this);
        volumeSliderObject.VolumeSlider.addListener(this);

        
    }
};
