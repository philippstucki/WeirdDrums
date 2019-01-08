/*
  ==============================================================================

    OscillatorSectionEditor.cpp
    Created: 6 Nov 2018 2:36:24pm
    Author:  dfila

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscillatorSectionEditor.h"

//==============================================================================
OscillatorSectionEditor::OscillatorSectionEditor(PatSynthAudioProcessor& p) 
	: processor(p)
{
	// Setup labels
	m_freqLabel.setText("osc freq", dontSendNotification);
	m_freqLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_freqLabel);

	m_attackLabel.setText("attack", dontSendNotification);
	m_attackLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_attackLabel);

	m_decayLabel.setText("decay", dontSendNotification);
	m_decayLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_decayLabel);

	m_pitchEnvAmountLabel.setText("env depth", dontSendNotification);
	m_pitchEnvAmountLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_pitchEnvAmountLabel);

	m_pitchEnvRateLabel.setText("env rate", dontSendNotification);
	m_pitchEnvRateLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_pitchEnvRateLabel);

	m_pitchLfoAmountLabel.setText("lfo depth", dontSendNotification);
	m_pitchLfoAmountLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_pitchLfoAmountLabel);

	m_pitchLfoRateLabel.setText("lfo rate", dontSendNotification);
	m_pitchLfoRateLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_pitchLfoRateLabel);

	// --
	frequencySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	frequencySlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&frequencySlider);
	frequencySliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdFreq,
		frequencySlider);

	// setup combo box
	oscComboBox.addItem(kMenuItemSineText,   kMenuItemSineId);
	oscComboBox.addItem(kMenuItemSawText,    kMenuItemSawId);
	oscComboBox.addItem(kMenuItemSquareText, kMenuItemSquareId);
	oscComboBox.setJustificationType(Justification::centred);
	addAndMakeVisible(&oscComboBox);
	oscComboBoxAttachment = new ComboBoxAttachment(
		processor.parameters, 
		Globals::paramIdWaveType, 
		oscComboBox);

	// amp attack/decay sliders
	attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	attackSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&attackSlider);
	attackSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdAttack,
		attackSlider);

	decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&decaySlider);
	decaySliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdDecay,
		decaySlider);

	// pitch env sliders
	pitchEnvAmountSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	pitchEnvAmountSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&pitchEnvAmountSlider);
	pitchEnvAmountAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdPitchEnvAmount,
		pitchEnvAmountSlider);

	pitchEnvRateSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	pitchEnvRateSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&pitchEnvRateSlider);
	pitchEnvRateSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdPitchEnvRate,
		pitchEnvRateSlider);

	// pitch lfo sliders
	pitchLfoAmountSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	pitchLfoAmountSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&pitchLfoAmountSlider);
	pitchLfoAmountAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdPitchLfoAmount,
		pitchLfoAmountSlider);

	pitchLfoRateSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	pitchLfoRateSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&pitchLfoRateSlider);
	pitchLfoRateSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdPitchLfoRate,
		pitchLfoRateSlider);
}

OscillatorSectionEditor::~OscillatorSectionEditor()
{
}

void OscillatorSectionEditor::paint (Graphics& g)
{
	g.setColour(Colours::blueviolet);
	g.fillRect(titleArea);

	g.setColour(Colours::white);
	g.drawText("OSC", titleArea, Justification::centred);
}

void OscillatorSectionEditor::resized()
{
	// Update rectangles sizes
	area = getLocalBounds();
	titleArea = area.removeFromTop(kTitleHeight);
	controlsArea = area;
	waveformArea = controlsArea.removeFromTop(kWaveformHeight);
	ampArea = controlsArea.removeFromRight(kAmpWidth);
	modArea = controlsArea.removeFromRight(kModWidth);

	// Add waevform selection combobox
	auto waveformComboBoxArea = waveformArea.removeFromTop(50);
	oscComboBox.setBounds(waveformComboBoxArea.reduced(12.5));

	// Add frequency slider
	
	{
		auto r = waveformArea.removeFromTop(50);
		frequencySlider.setBounds(r.removeFromTop(25));
		m_freqLabel.setBounds(r);
	}

	// Add attack/decay sliders
	{
		auto r = ampArea.removeFromLeft(50);
		attackSlider.setBounds(r);
		// TODO: label
	}

	{
		auto r = ampArea.removeFromLeft(50);
		decaySlider.setBounds(r);
		// TODO: label
	}

	// add pitch envelope (rotary) sliders
	auto pitchEnvSlidersArea = modArea.removeFromRight(75);

	{
		auto r = pitchEnvSlidersArea.removeFromTop(75);
		pitchEnvAmountSlider.setBounds(r.removeFromTop(60));
		m_pitchEnvAmountLabel.setBounds(r);
	}
	
	{
		auto r = pitchEnvSlidersArea.removeFromTop(75);
		pitchEnvRateSlider.setBounds(r.removeFromTop(60));
		m_pitchEnvRateLabel.setBounds(r);
	}

	// add pitch lfo (rotary) sliders
	auto pitchLfoSlidersArea = modArea.removeFromRight(75);

	{
		auto r = pitchLfoSlidersArea.removeFromTop(75);
		pitchLfoAmountSlider.setBounds(r.removeFromTop(60));
		m_pitchLfoAmountLabel.setBounds(r);
	}

	{
		auto r = pitchLfoSlidersArea.removeFromTop(75);
		pitchLfoRateSlider.setBounds(r.removeFromTop(60));
		m_pitchLfoRateLabel.setBounds(r);
	}
}
