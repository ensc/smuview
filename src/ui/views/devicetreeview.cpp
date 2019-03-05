/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2019 Frank Stettner <frank-stettner@gmx.net>
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

#include <memory>

#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QVBoxLayout>

#include "devicetreeview.hpp"
#include "src/session.hpp"
#include "src/devices/basedevice.hpp"
#include "src/ui/devices/devicetree/devicetreeview.hpp"
#include "src/ui/views/baseview.hpp"

using std::shared_ptr;

namespace sv {
namespace ui {
namespace views {

DeviceTreeView::DeviceTreeView(const Session &session,
		QWidget *parent) :
	BaseView(session, parent),
	action_add_device_(new QAction(this)),
	action_add_virtualdevice_(new QAction(this)),
	action_disconnect_device_(new QAction(this))
{
	setup_ui();
	setup_toolbar();
	connect_signals();
}

QString DeviceTreeView::title() const
{
	return tr("Device Tree");
}

void DeviceTreeView::setup_ui()
{
	QVBoxLayout *layout = new QVBoxLayout();
	device_tree_ = new devices::devicetree::DeviceTreeView(session(),
		false, false, false, false, false, false);
	layout->addWidget(device_tree_);
	layout->setContentsMargins(2, 2, 2, 2);

	this->central_widget_->setLayout(layout);
}

void DeviceTreeView::setup_toolbar()
{

	action_add_device_->setText(tr("Add device"));
	action_add_device_->setIcon(
		QIcon::fromTheme("network-connect",
		QIcon(":/icons/network-connect.png")));
	connect(action_add_device_, SIGNAL(triggered(bool)),
		this, SLOT(on_action_add_device_triggered()));

	action_add_virtualdevice_->setText(tr("Add virtual device"));
	action_add_virtualdevice_->setIcon(
		QIcon::fromTheme("user-identity",
		QIcon(":/icons/user-identity.png")));
	connect(action_add_virtualdevice_, SIGNAL(triggered(bool)),
		this, SLOT(on_action_add_virtualdevice_triggered()));

	action_disconnect_device_->setText(tr("Disconnect device"));
	action_disconnect_device_->setIcon(
		QIcon::fromTheme("network-disconnect",
		QIcon(":/icons/network-disconnect.png")));
	connect(action_disconnect_device_, SIGNAL(triggered(bool)),
		this, SLOT(on_action_disconnect_device_triggered()));

	toolbar_ = new QToolBar("Device Tree Toolbar");
	toolbar_->addAction(action_add_device_);
	toolbar_->addAction(action_add_virtualdevice_);
	toolbar_->addAction(action_disconnect_device_);
	this->addToolBar(Qt::TopToolBarArea, toolbar_);
}

void DeviceTreeView::connect_signals()
{
}

void DeviceTreeView::on_action_add_device_triggered()
{
}

void DeviceTreeView::on_action_add_virtualdevice_triggered()
{
}

void DeviceTreeView::on_action_disconnect_device_triggered()
{
}

} // namespace views
} // namespace ui
} // namespace sv

