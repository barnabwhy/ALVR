#pragma once

#include <openvr_driver.h>
#include "bindings.h"

class FakeViveTracker final : public vr::ITrackedDeviceServerDriver
{
	vr::TrackedDeviceIndex_t m_unObjectId;
   	const char* m_name;
	vr::DriverPose_t m_pose = {};
public:

    FakeViveTracker(const char* name);

    FakeViveTracker(const FakeViveTracker&) = delete;
    FakeViveTracker& operator=(const FakeViveTracker&) = delete;

    inline const char* GetSerialNumber() const {
		return std::string("ALVR Tracker ").append(m_name).c_str();
	}

    inline const char* GetName() const {
		return std::string("ALVR/tracker/").append(m_name).c_str();
	}

    virtual vr::EVRInitError Activate( vr::TrackedDeviceIndex_t unObjectId ) override;
    
    virtual inline void Deactivate() override
	{
		m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
	}

	virtual inline void EnterStandby() override {}	
	virtual inline void *GetComponent( const char */*pchComponentNameAndVersion*/ ) override
	{
		// override this to add a component to a driver
		return nullptr;
	}

	virtual inline void DebugRequest( const char */*pchRequest*/, char *pchResponseBuffer, uint32_t unResponseBufferSize ) override
	{
		if ( unResponseBufferSize >= 1 )
			pchResponseBuffer[0] = 0;
	}
    
	virtual vr::DriverPose_t GetPose() override;

    void OnPoseUpdated(uint64_t targetTimestampNs, FfiBodyTracker tracker);
};