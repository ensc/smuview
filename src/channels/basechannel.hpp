/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
 * Copyright (C) 2016 Soeren Apel <soeren@apelpie.net>
 * Copyright (C) 2016-2018 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHANNELS_BASECHANNEL_HPP
#define CHANNELS_BASECHANNEL_HPP

#include <memory>
#include <set>
#include <utility>
#include <vector>

#include <QColor>
#include <QObject>
#include <QSettings>

#include "src/data/datautil.hpp"

using std::map;
using std::pair;
using std::set;
using std::shared_ptr;
using std::vector;

namespace sv {

namespace data {
class BaseSignal;
}

namespace devices {
class Device;
}

namespace channels {

enum class ChannelType {
	/**
	 * Channels with analog data (Power supplies, loads, DMMs)
	 */
	AnalogChannel,
	/**
	 * Virtual channel generated by math operations
	 */
	MathChannel
};

class BaseChannel :
	public QObject,
	public std::enable_shared_from_this<BaseChannel>
{
	Q_OBJECT

public:
	BaseChannel(
		shared_ptr<devices::Device> parent_device,
		const QString channel_group_name, // TODO: replace with ? object?
		double channel_start_timestamp);
	virtual ~BaseChannel();

public:
	// TODO: merge with Configurable::measured_quantity_t
	typedef pair<data::Quantity, set<data::QuantityFlag>> quantity_t;

	/**
	 * Returns enabled status of this channel.
	 */
	virtual bool enabled() const;

	/**
	 * Sets the enabled status of this channel.
	 * @param value Boolean value to set.
	 */
	virtual void set_enabled(bool value);

	/**
	 * Gets the type of this channel.
	 */
	ChannelType type() const;

	/**
	 * Gets the index number of this channel, i.e. a unique ID assigned by
	 * the device driver.
	 */
	virtual unsigned int index() const = 0;

	/**
	 * Does this channel have just one signal, thats quantity doesn't chege?
	 */
	bool has_fixed_signal();

	/**
	 * Sets if this channel has just one signal, thats quantity doesn't chege
	 */
	void set_fixed_signal(bool has_fixed_signal);

	/**
	 * Gets the actual signal
	 */
	shared_ptr<data::BaseSignal> actual_signal();

	/**
	 * Get all signals for this channel
	 */
	map<quantity_t, shared_ptr<data::BaseSignal>> signal_map();

	/**
	 * Returns the device, this channel belongs to.
	 */
	shared_ptr<devices::Device> parent_device();

	/**
	 * Get the channel group name, the channel is in. Returns "" if the channel
	 * is not in a channel group.
	 *
	 * TODO: Change to vector<QString>, bc the channel can be in more than one
	 *       channel group (see "demo" driver)
	 */
	QString channel_group_name() const;

	/**
	 * Gets the name of this channel, i.e. how the device calls it.
	 */
	QString name() const;

	/**
	 * Sets the name of the signal.
	 */
	virtual void set_name(QString name);

	/**
	 * Gets the display name of this channel.
	 */
	QString display_name() const;

	/**
	 * Get the colour of the signal.
	 */
	QColor colour() const;

	/**
	 * Set the colour of the signal.
	 */
	void set_colour(QColor colour);

	/**
	 * Inits a signal
	 *
	 * TODO: Implement here!
	 */
	/*
	virtual shared_ptr<data::BaseSignal> init_signal(
		data::Quantity quantity,
		set<data::QuantityFlag> quantity_flags,
		data::Unit unit) = 0;
	*/

	virtual void save_settings(QSettings &settings) const;
	virtual void restore_settings(QSettings &settings);

protected:
	ChannelType channel_type_;
	double channel_start_timestamp_;
	bool has_fixed_signal_;

	shared_ptr<data::BaseSignal> actual_signal_;
	map<quantity_t, shared_ptr<data::BaseSignal>> signal_map_;

	shared_ptr<devices::Device> parent_device_;
	const QString channel_group_name_; // TODO: better way?
	QString name_;
	QColor colour_;

public Q_SLOTS:
	void on_aquisition_start_timestamp_changed(double);

Q_SIGNALS:
	void channel_start_timestamp_changed(double);
	void enabled_changed(const bool);
	void name_changed(const QString);
	void colour_changed(const QColor);
	void signal_added(shared_ptr<data::BaseSignal>);
	void signal_changed(shared_ptr<data::BaseSignal>);

};

} // namespace channels
} // namespace sv

#endif // CHANNELS_BASECHANNEL_HPP
