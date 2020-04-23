/*
    Copyright (c) 2020 Dmitry Baryshev

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <QLabel>
#include <QSlider>

#include <sail/sail-common.h>
#include <sail/sail-c++.h>

#include "readoptions.h"
#include "ui_readoptions.h"

class Q_DECL_HIDDEN ReadOptions::Private
{
public:
    QScopedPointer<Ui::ReadOptions> ui;
};

ReadOptions::ReadOptions(const QString &codecDescription, const sail::read_features &read_features, QWidget *parent)
    : QDialog(parent)
    , d(new Private)
{
    d->ui.reset(new Ui::ReadOptions);
    d->ui->setupUi(this);

    d->ui->labelCodec->setText(codecDescription);

    init(read_features);
}

ReadOptions::~ReadOptions()
{
}

int ReadOptions::pixelFormat() const
{
    return d->ui->comboColor->currentData().toInt();
}

sail_error_t ReadOptions::init(const sail::read_features &read_features)
{
    if (read_features.output_pixel_formats().empty()) {
        d->ui->labelColor->setText(tr("Output color selection is not available"));
        d->ui->labelColor->setEnabled(false);
        d->ui->comboColor->setEnabled(false);
    } else {
        d->ui->labelColor->setText(tr("Output color:"));

        const char *output_pixel_format_str;

        for (int output_pixel_format : read_features.output_pixel_formats()) {
            SAIL_TRY(sail_pixel_format_to_string(output_pixel_format, &output_pixel_format_str));

            d->ui->comboColor->addItem(output_pixel_format_str,
                                       /* user data */ output_pixel_format);
        }

        SAIL_TRY(sail_pixel_format_to_string(read_features.preferred_output_pixel_format(), &output_pixel_format_str));
        d->ui->comboColor->setCurrentText(output_pixel_format_str);
    }

    return 0;
}