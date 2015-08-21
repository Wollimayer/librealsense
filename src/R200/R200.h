#pragma once

#ifndef LIBREALSENSE_R200_CAMERA_H
#define LIBREALSENSE_R200_CAMERA_H

#include "../UVCCamera.h"
#include "HardwareIO.h"

#ifdef USE_UVC_DEVICES
namespace r200
{
    class R200Camera : public rs::UVCCamera
    {
        CameraCalibrationParameters calib;
    public:
        R200Camera(uvc_context_t * ctx, uvc_device_t * device);
        ~R200Camera();

        int GetStreamSubdeviceNumber(int stream) const override final;
        void RetrieveCalibration() override final;
        void SetStreamIntent(bool depth, bool color) override final;

        void EnableStreamPreset(int streamIdentifier, int preset) override final
        {
            switch(streamIdentifier)
            {
            case RS_DEPTH: EnableStream(RS_DEPTH, 480, 360, 0, RS_Z16); break;
            case RS_COLOR: EnableStream(RS_COLOR, 640, 480, 60, RS_RGB); break;
            default: throw std::runtime_error("unsupported stream");
            }
        }

        float GetDepthScale() const override final { return 0.001f; } // convert mm to m
    };
} // end namespace r200
#endif

#endif
