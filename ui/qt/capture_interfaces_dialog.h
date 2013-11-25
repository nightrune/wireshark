/* capture_interfaces_dialog.h
 *
 * $Id$
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef CAPTURE_INTERFACES_DIALOG_H
#define CAPTURE_INTERFACES_DIALOG_H

#include <QDialog>
#include <QTableWidget>

#include "interface_tree.h"
#include "preferences_dialog.h"

/*
 * Symbolic names for column indices.
 */
enum
{
    CAPTURE = 0,
    INTERFACE,
    TRAFFIC,
    LINK,
    PMODE,
    SNAPLEN,
#if defined(HAVE_PCAP_CREATE)
    BUFFER,
    MONITOR,
#elif defined(_WIN32) && !defined(HAVE_PCAP_CREATE)
    BUFFER,
#endif
    FILTER,
    NUM_COLUMNS
};


namespace Ui {
class CaptureInterfacesDialog;
}

class CaptureInterfacesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CaptureInterfacesDialog(QWidget *parent = 0);
    ~CaptureInterfacesDialog();

    void SetTab(int index);
    void UpdateInterfaces();
    //void updateStatistics(void);

private slots:
    void on_capturePromModeCheckBox_toggled(bool checked);
    void on_cbStopCaptureAuto_toggled(bool checked);
    void on_cbUpdatePacketsRT_toggled(bool checked);
    void on_cbAutoScroll_toggled(bool checked);
    void on_cbNewFileAuto_toggled(bool checked);
    void on_cbExtraCaptureInfo_toggled(bool checked);
    void on_cbResolveMacAddresses_toggled(bool checked);
    void on_cbResolveNetworkNames_toggled(bool checked);
    void on_cbResolveTransportNames_toggled(bool checked);
    void on_bStart_clicked();
    void on_bStop_clicked();
    void tableItemClicked(QTableWidgetItem * item);
    void updateStatistics(void);
    void on_tbInterfaces_hideEvent(QHideEvent *evt);
    void on_tbInterfaces_showEvent(QShowEvent *evt);

signals:
    void startCapture();
    void stopCapture();
    void getPoints(int row, PointList *pts);

private:
    Ui::CaptureInterfacesDialog *ui;
    Qt::CheckState m_pressedItemState;

#ifdef HAVE_LIBPCAP
    if_stat_cache_t *stat_cache_;
    QTimer *stat_timer_;
#endif // HAVE_LIBPCAP
};

#endif // CAPTURE_INTERFACES_DIALOG_H

/*
 * Editor modelines
 *
 * Local Variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * ex: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */