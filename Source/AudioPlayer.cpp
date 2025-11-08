#include "AudioPlayer.h"

clsAudioPlayer::clsAudioPlayer()
{
    formatManager.registerBasicFormats();
}

clsAudioPlayer::~clsAudioPlayer()
{
    releaseResources();
}
bool clsAudioPlayer::IsPlaying()
{
    return IsPlay;
}
//audio
void clsAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    storedBlockSize = samplesPerBlockExpected;
    storedSampleRate = sampleRate;
    if (resampleSource)
        resampleSource->prepareToPlay(samplesPerBlockExpected, sampleRate);
    else
        transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
//audio
void clsAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (resampleSource)
        resampleSource->getNextAudioBlock(bufferToFill);
    else
        transportSource.getNextAudioBlock(bufferToFill);

    
    if (isABLooping)
    {
        double currentPos = transportSource.getCurrentPosition();
        if (currentPos >= loopEnd)
        {
            transportSource.setPosition(loopStart); 
            transportSource.start();                
        }
    }

}

//audio
void clsAudioPlayer::releaseResources()
{
    // stop and detach transport then release
    transportSource.stop();
    transportSource.setSource(nullptr);
    transportSource.releaseResources();

    resampleSource.reset();
    readerSource.reset();
}

bool clsAudioPlayer::LoadAudioFile(const juce::File& File)
{
    if (auto* reader = formatManager.createReaderFor(File))
    {
        // ?? Disconnect old source first
        transportSource.stop();
        transportSource.setSource(nullptr);
        resampleSource.reset();
        readerSource.reset();

        // Create new reader source
        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

        // Attach safely
        transportSource.setSource(readerSource.get(), 0, nullptr, storedSampleRate);

        // Create a resampler that wraps the transport (resampler does NOT own transport)
        resampleSource = std::make_unique<juce::ResamplingAudioSource>(&transportSource, false);
        resampleSource->prepareToPlay(storedBlockSize, storedSampleRate);
        lastLoadedFile = File;
        sendChangeMessage();

        

        // Store file info
        lastLoadedFile = File;
        currentFileName = File.getFileName();
        currentFilePath = File.getFullPathName();
        durationInSeconds = static_cast<double>(readerSource->getTotalLength()) / storedSampleRate;

        return true;

    }
    return false;

}

void clsAudioPlayer::PlayAudio()
{
    IsPlay = true;
    if (transportSource.getLengthInSeconds() > 0.0)
    {
        transportSource.start();
    }
}

void clsAudioPlayer::LoopingAudio(bool IsLooping)

{
   if (readerSource != nullptr)
        readerSource->setLooping(IsLooping);

}
void clsAudioPlayer::LoopAudioFromAToB(double a, double b)
{
    isABLooping = true;
    loopStart = a;
    loopEnd = b;
    isABLooping = true;

    transportSource.setPosition(loopStart); 
    transportSource.start();                 

}
bool clsAudioPlayer::StopAudio()
{
    transportSource.stop();
    IsPlay = false;
    return true;
}

void clsAudioPlayer::MuteUnmute() {
    if (!isMuted) {
        previousGain = transportSource.getGain();
        transportSource.setGain(0.0f);
        isMuted = true;

    }
    else {
        transportSource.setGain(previousGain);
        isMuted = false;
    }
}

void clsAudioPlayer::startAudio() {

    transportSource.setPosition(0.0);
    transportSource.start();

}

void clsAudioPlayer::EndAudio() {

    if (readerSource != nullptr)
    {
        auto* reader = readerSource->getAudioFormatReader();
        if (reader != nullptr)
        {
            if (reader->sampleRate <= 0.0)
                return;

            TrackLengthInSeconds = reader->lengthInSamples / reader->sampleRate;
            transportSource.setPosition(TrackLengthInSeconds);
        }
    }
}



// Helpear function to format seconds to MM:SS
juce::String clsAudioPlayer::formatSecondsToMMSS(double seconds)
{
    int totalSeconds = static_cast<int>(seconds);
    int minutes = totalSeconds / 60;
    int secs = totalSeconds % 60;
    return juce::String::formatted("%02d:%02d", minutes, secs);
}

void clsAudioPlayer::SetGain(float Gain)
{
    transportSource.setGain(Gain);
}
void clsAudioPlayer::SetPosition(double Pos)
{
    transportSource.setPosition(Pos);
}
double clsAudioPlayer::GetPosition() const
{
    return transportSource.getCurrentPosition();
}
double clsAudioPlayer::GetLength() const
{
    return transportSource.getLengthInSeconds();
}
double clsAudioPlayer::GetGain() const
{
    return transportSource.getGain();
}
juce::ResamplingAudioSource* clsAudioPlayer::getResamplingSource() const {
    return resampleSource.get();
}
juce::AudioFormatManager* clsAudioPlayer::getFormatManager() const {
    return const_cast<juce::AudioFormatManager*>(&formatManager);
}
juce::AudioTransportSource* clsAudioPlayer::getTransportSource() const {
    return const_cast<juce::AudioTransportSource*>(&transportSource);
}
juce::File clsAudioPlayer::getLastLoadedFile() const {
    return lastLoadedFile;
}

juce::String clsAudioPlayer::formatSecondsToHHMMSS(double seconds)
{
    int totalSeconds = static_cast<int>(seconds);
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds / 60) % 60;
    int secs = totalSeconds % 60;

    return juce::String::formatted("%02d:%02d:%02d", hours, minutes, secs);
}
void clsAudioPlayer::ReverseAudio(juce::AudioBuffer<float>& buffer)
{
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();

    for (int ch = 0; ch < numChannels; ++ch)
    {
        float* data = buffer.getWritePointer(ch);
        for (int i = 0; i < numSamples / 2; ++i)
            std::swap(data[i], data[numSamples - 1 - i]);

    }
}
void clsAudioPlayer::GoBack()
{
    double currentPos = transportSource.getCurrentPosition() - 5;
    if (currentPos < 0)
        currentPos = 0;
    transportSource.setPosition(currentPos);
   
    transportSource.start();
}
void clsAudioPlayer::GoForward()
{
    double currentPos = transportSource.getCurrentPosition() + 5;
    if (currentPos > transportSource.getLengthInSeconds())
        currentPos = transportSource.getLengthInSeconds();
    transportSource.setPosition(currentPos);
    transportSource.start();
}
