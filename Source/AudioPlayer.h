#pragma once
#include <JuceHeader.h>
class clsAudioPlayer: public juce::ChangeBroadcaster
{
private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    

    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::ResamplingAudioSource> resampleSource;
    juce::File lastLoadedFile;
	int storedBlockSize;
	double storedSampleRate;
    juce::File currentFile;

   

    double loopStart = 0.0;
    double loopEnd = 0.0;
    bool isABLooping = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsAudioPlayer);

public:
    clsAudioPlayer();
    ~clsAudioPlayer();

    //Audio Data
    juce::String currentFileName;
    juce::String currentFilePath;
    double durationInSeconds = 0.0;

    bool IsPlay;
	bool isMuted = false;
    float previousGain;
    double TrackLengthInSeconds = 0.0;
    double DurationSeconds; // store duration

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    bool LoadAudioFile(const juce::File& File);
    void PlayAudio();
    bool StopAudio();
    void LoopingAudio(bool IsLooping);
    void MuteUnmute();
    void startAudio();
    void EndAudio();
    void LoopAudioFromAToB(double a, double b);


    
	// Utility function to format seconds to MM:SS
    static juce::String formatSecondsToMMSS(double seconds);

    
    void SetGain(float Gain);
    void SetPosition(double Position);
    double GetPosition() const;
    double GetGain() const;
    double GetLength() const;
    juce::ResamplingAudioSource* getResamplingSource() const;
    juce::AudioFormatManager* getFormatManager() const;
    juce::AudioTransportSource* getTransportSource() const;
    juce::File getLastLoadedFile() const;
    juce::String formatSecondsToHHMMSS(double seconds);
    void ReverseAudio(juce::AudioBuffer<float>& buffer);
    void GoBack();
    void GoForward();
    bool IsPlaying();
    
};