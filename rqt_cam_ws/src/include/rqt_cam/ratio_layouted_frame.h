/*
 * Copyright (c) 2020, e-consystems
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the e-consystems nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef rqt_cam__RatioLayoutedFrame_H
#define rqt_cam__RatioLayoutedFrame_H

#include <QFrame>
#include <QImage>
#include <QLayout>
#include <QLayoutItem>
#include <QMutex>
#include <QPainter>
#include <QRect>
#include <QSize>
#include <QWidget>
#include <QObject>

namespace rqt_cam {

/**
* RatioLayoutedFrame is a layout containing a single frame with a fixed aspect ratio.
* The default aspect ratio is 4:3.
*/
  class RatioLayoutedFrame : public QFrame
  {

    Q_OBJECT

    private:

      static int greatestCommonDivisor(int a, int b);

      void mousePressEvent(QMouseEvent * mouseEvent);

      QVBoxLayout* outer_layout_;

      QSize aspect_ratio_;

      QImage qimage_;

      mutable QMutex qimage_mutex_;

    protected slots:

      void onSmoothImageChanged(bool checked);

    signals:

      void delayed_update();

      void mouseLeft(int x, int y);

    protected:

      void setAspectRatio(unsigned short width, unsigned short height);

      void paintEvent(QPaintEvent* event);

      bool smoothImage_;

    public:

      RatioLayoutedFrame(QWidget* parent, Qt::WindowFlags flags = 0);

      virtual ~RatioLayoutedFrame();

      const QImage& getImage() const;

      QImage getImageCopy() const;

      void setImage(const QImage& image);

      QRect getAspectRatioCorrectPaintArea();

      void resizeToFitAspectRatio();

      void setOuterLayout(QVBoxLayout* outer_layout);

      void setInnerFrameMinimumSize(const QSize& size);

      void setInnerFrameMaximumSize(const QSize& size);

      void setInnerFrameFixedSize(const QSize& size);

  };

}

#endif // rqt_cam__RatioLayoutedFrame_H
