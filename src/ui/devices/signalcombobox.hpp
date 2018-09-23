/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2018 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UI_DEVICES_SIGNALCOMBOBOX_HPP
#define UI_DEVICES_SIGNALCOMBOBOX_HPP

#include <memory>

#include <QComboBox>
#include <QString>
#include <QWidget>

using std::shared_ptr;

namespace sv {

class Session;

namespace channels {
class BaseChannel;
}

namespace data {
class BaseSignal;
}

namespace ui {
namespace devices {

class SignalComboBox : public QComboBox
{
	Q_OBJECT

public:
	SignalComboBox(
		const Session &session, shared_ptr<sv::channels::BaseChannel> channel,
		QWidget *parent = nullptr);

	void select_signal(shared_ptr<sv::data::BaseSignal>);
	shared_ptr<sv::data::BaseSignal> selected_signal() const;

private:
	const Session &session_;
	shared_ptr<sv::channels::BaseChannel> channel_;

	void setup_ui();

public Q_SLOTS:
	void change_channel(shared_ptr<sv::channels::BaseChannel>);
};

} // namespace devices
} // namespace ui
} // namespace sv

#endif // UI_DEVICES_SIGNALCOMBOBOX_HPP
