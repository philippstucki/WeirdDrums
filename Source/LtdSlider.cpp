/*
  ==============================================================================

    LtdSlider.cpp
    Created: 5 Mar 2019 8:38:02am
    Author:  dfila

  ==============================================================================
*/

#include "LtdSlider.h"

LtdSlider::LtdSlider (juce::String label)
{
	// Set up name label
	m_nameLabel.setFont(Font(15.0f, Font::bold));
	m_nameLabel.setText (label, dontSendNotification);
	m_nameLabel.setJustificationType (Justification::centred);
	addAndMakeVisible (m_nameLabel);

	// Set up value label
	//m_valueLabel.setFont(Font(15.0f, Font::bold));
	//m_valueLabel.setJustificationType(Justification::centred);
	//addAndMakeVisible(m_valueLabel);

	// update label whenever slider value changes
	//m_slider.onValueChange = [&] { m_valueLabel.setText(m_slider.getTextFromValue(m_slider.getValue()), sendNotification); };
};

LtdSlider::~LtdSlider()
{
	// TODO (probably nothing)
}

Slider* LtdSlider::getSlider()
{
	return &m_slider;
}