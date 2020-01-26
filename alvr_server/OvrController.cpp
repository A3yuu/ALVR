#include "OvrController.h"

// Left hand open gesture transformation, thanks to https://github.com/spayne and his soft_knuckles repository
extern const vr::VRBoneTransform_t g_openHandGesture[31U] = {
	{ { 0.000000f, 0.000000f, 0.000000f, 1.000000f }, { 1.000000f, -0.000000f, -0.000000f, 0.000000f } },
	{ { -0.034038f, 0.036503f, 0.164722f, 1.000000f }, { -0.055147f, -0.078608f, -0.920279f, 0.379296f } },
	{ { -0.012083f, 0.028070f, 0.025050f, 1.000000f }, { 0.464112f, 0.567418f, 0.272106f, 0.623374f } },
	{ { 0.040406f, 0.000000f, -0.000000f, 1.000000f }, { 0.994838f, 0.082939f, 0.019454f, 0.055130f } },
	{ { 0.032517f, 0.000000f, 0.000000f, 1.000000f }, { 0.974793f, -0.003213f, 0.021867f, -0.222015f } },
	{ { 0.030464f, -0.000000f, -0.000000f, 1.000000f }, { 1.000000f, -0.000000f, -0.000000f, 0.000000f } },
	{ { 0.000632f, 0.026866f, 0.015002f, 1.000000f }, { 0.644251f, 0.421979f, -0.478202f, 0.422133f } },
	{ { 0.074204f, -0.005002f, 0.000234f, 1.000000f }, { 0.995332f, 0.007007f, -0.039124f, 0.087949f } },
	{ { 0.043930f, -0.000000f, -0.000000f, 1.000000f }, { 0.997891f, 0.045808f, 0.002142f, -0.045943f } },
	{ { 0.028695f, 0.000000f, 0.000000f, 1.000000f }, { 0.999649f, 0.001850f, -0.022782f, -0.013409f } },
	{ { 0.022821f, 0.000000f, -0.000000f, 1.000000f }, { 1.000000f, -0.000000f, 0.000000f, -0.000000f } },
	{ { 0.002177f, 0.007120f, 0.016319f, 1.000000f }, { 0.546723f, 0.541276f, -0.442520f, 0.460749f } },
	{ { 0.070953f, 0.000779f, 0.000997f, 1.000000f }, { 0.980294f, -0.167261f, -0.078959f, 0.069368f } },
	{ { 0.043108f, 0.000000f, 0.000000f, 1.000000f }, { 0.997947f, 0.018493f, 0.013192f, 0.059886f } },
	{ { 0.033266f, 0.000000f, 0.000000f, 1.000000f }, { 0.997394f, -0.003328f, -0.028225f, -0.066315f } },
	{ { 0.025892f, -0.000000f, 0.000000f, 1.000000f }, { 0.999195f, -0.000000f, 0.000000f, 0.040126f } },
	{ { 0.000513f, -0.006545f, 0.016348f, 1.000000f }, { 0.516692f, 0.550143f, -0.495548f, 0.429888f } },
	{ { 0.065876f, 0.001786f, 0.000693f, 1.000000f }, { 0.990420f, -0.058696f, -0.101820f, 0.072495f } },
	{ { 0.040697f, 0.000000f, 0.000000f, 1.000000f }, { 0.999545f, -0.002240f, 0.000004f, 0.030081f } },
	{ { 0.028747f, -0.000000f, -0.000000f, 1.000000f }, { 0.999102f, -0.000721f, -0.012693f, 0.040420f } },
	{ { 0.022430f, -0.000000f, 0.000000f, 1.000000f }, { 1.000000f, 0.000000f, 0.000000f, 0.000000f } },
	{ { -0.002478f, -0.018981f, 0.015214f, 1.000000f }, { 0.526918f, 0.523940f, -0.584025f, 0.326740f } },
	{ { 0.062878f, 0.002844f, 0.000332f, 1.000000f }, { 0.986609f, -0.059615f, -0.135163f, 0.069132f } },
	{ { 0.030220f, 0.000000f, 0.000000f, 1.000000f }, { 0.994317f, 0.001896f, -0.000132f, 0.106446f } },
	{ { 0.018187f, 0.000000f, 0.000000f, 1.000000f }, { 0.995931f, -0.002010f, -0.052079f, -0.073526f } },
	{ { 0.018018f, 0.000000f, -0.000000f, 1.000000f }, { 1.000000f, 0.000000f, 0.000000f, 0.000000f } },
	{ { -0.006059f, 0.056285f, 0.060064f, 1.000000f }, { 0.737238f, 0.202745f, 0.594267f, 0.249441f } },
	{ { -0.040416f, -0.043018f, 0.019345f, 1.000000f }, { -0.290331f, 0.623527f, -0.663809f, -0.293734f } },
	{ { -0.039354f, -0.075674f, 0.047048f, 1.000000f }, { -0.187047f, 0.678062f, -0.659285f, -0.265683f } },
	{ { -0.038340f, -0.090987f, 0.082579f, 1.000000f }, { -0.183037f, 0.736793f, -0.634757f, -0.143936f } },
	{ { -0.031806f, -0.087214f, 0.121015f, 1.000000f }, { -0.003659f, 0.758407f, -0.639342f, -0.126678f } }
};
extern const vr::VRBoneTransform_t handRestPose[31U] = {
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 1 }, { 0, 0, 0, 0 } },
};



OvrController::OvrController(bool isLeftHand, int index)
	: m_isLeftHand(isLeftHand)
	, m_unObjectId(vr::k_unTrackedDeviceIndexInvalid)
	, m_index(index)
{
	memset(&m_pose, 0, sizeof(m_pose));
	m_pose.poseIsValid = true;
	m_pose.result = vr::TrackingResult_Running_OK;
	m_pose.deviceIsConnected = true;

	//controller is rotated and translated, prepare pose
	double rotation[3] = { 0.0, 0.0, 36 * M_PI / 180 };
	m_pose.qDriverFromHeadRotation = EulerAngleToQuaternion(rotation);

	vr::HmdVector3d_t offset;
	offset.v[0] =	0;
	offset.v[1] =	0.009;
	offset.v[2] = -0.053;

	vr::HmdVector3d_t offetRes = vrmath::quaternionRotateVector(m_pose.qDriverFromHeadRotation, offset, false);

	m_pose.vecDriverFromHeadTranslation[0] = offetRes.v[0];
	m_pose.vecDriverFromHeadTranslation[1] = offetRes.v[1];
	m_pose.vecDriverFromHeadTranslation[2] = offetRes.v[2];

	m_pose.qWorldFromDriverRotation = HmdQuaternion_Init(1, 0, 0, 0);

	m_pose.qRotation = HmdQuaternion_Init(1, 0, 0, 0);

	//init handles
	for (int i = 0; i < ALVR_INPUT_COUNT; i++) {
		m_handles[i] = vr::k_ulInvalidInputComponentHandle;
	}

}


bool OvrController::GetHand() {
	return m_isLeftHand;
}

//
// ITrackedDeviceServerDriver
//

vr::EVRInitError OvrController::Activate(vr::TrackedDeviceIndex_t unObjectId)
{
	Log(L"RemoteController::Activate. objectId=%d", unObjectId);
	
	m_unObjectId = unObjectId;
	m_ulPropertyContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_unObjectId);

	//from leap
	vr::VRProperties()->SetBoolProperty(m_ulPropertyContainer, vr::Prop_WillDriftInYaw_Bool, false);
	vr::VRProperties()->SetBoolProperty(m_ulPropertyContainer, vr::Prop_DeviceIsWireless_Bool, false);
	vr::VRProperties()->SetInt32Property(m_ulPropertyContainer, vr::Prop_DeviceClass_Int32, vr::TrackedDeviceClass_Controller);
	vr::VRProperties()->SetInt32Property(m_ulPropertyContainer, vr::Prop_Axis0Type_Int32, vr::k_eControllerAxis_TrackPad);
	vr::VRProperties()->SetInt32Property(m_ulPropertyContainer, vr::Prop_Axis1Type_Int32, vr::k_eControllerAxis_Trigger);
	vr::VRProperties()->SetUint64Property(m_ulPropertyContainer, vr::Prop_HardwareRevision_Uint64, 1515);
	vr::VRProperties()->SetUint64Property(m_ulPropertyContainer, vr::Prop_FirmwareVersion_Uint64, 1515);
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_ResourceRoot_String, "indexcontroller");
	
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_TrackingSystemName_String, Settings::Instance().m_controllerTrackingSystemName.c_str());
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_ManufacturerName_String, Settings::Instance().m_controllerManufacturerName.c_str());
	//vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_ModelNumber_String, m_isLeftHand ? (Settings::Instance().m_controllerModelNumber + " (Left Controller)").c_str() : (Settings::Instance().m_controllerModelNumber + " (Right Controller)").c_str());
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_ModelNumber_String, m_isLeftHand ? "Knuckles Left" : "Knuckles Right");

	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_RenderModelName_String, m_isLeftHand ? Settings::Instance().m_controllerRenderModelNameLeft.c_str() : Settings::Instance().m_controllerRenderModelNameRight.c_str());
	
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_SerialNumber_String, GetSerialNumber().c_str());
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_AttachedDeviceId_String, GetSerialNumber().c_str());
	//vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_RegisteredDeviceType_String, m_isLeftHand ? (Settings::Instance().mControllerRegisteredDeviceType + "_Left").c_str() : (Settings::Instance().mControllerRegisteredDeviceType + "_Right").c_str() );
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_RegisteredDeviceType_String, m_isLeftHand ? "valve/index_controllerLHR-E217CD00" : "valve/index_controllerLHR-E217CD01"); // Changed

	//uint64_t supportedButtons = 0xFFFFFFFFFFFFFFFFULL;
	//vr::VRProperties()->SetUint64Property(m_ulPropertyContainer, vr::Prop_SupportedButtons_Uint64, supportedButtons);
	vr::VRProperties()->SetUint64Property(m_ulPropertyContainer, vr::Prop_SupportedButtons_Uint64,
		vr::ButtonMaskFromId(vr::k_EButton_System) |
		vr::ButtonMaskFromId(vr::k_EButton_IndexController_A) |
		vr::ButtonMaskFromId(vr::k_EButton_IndexController_B) |
		vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad) |
		vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Trigger)
	);
	
	vr::VRProperties()->SetBoolProperty(m_ulPropertyContainer, vr::Prop_DeviceProvidesBatteryStatus_Bool, true);
	
	
	//vr::VRProperties()->SetInt32Property(m_ulPropertyContainer, vr::Prop_Axis0Type_Int32, vr::k_eControllerAxis_Joystick);
	
	vr::VRProperties()->SetInt32Property(m_ulPropertyContainer, vr::Prop_ControllerRoleHint_Int32, m_isLeftHand ? vr::TrackedControllerRole_LeftHand : vr::TrackedControllerRole_RightHand);
	
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_ControllerType_String, Settings::Instance().m_controllerType.c_str());
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_InputProfilePath_String, Settings::Instance().m_controllerInputProfilePath.c_str());
	int i = 0;
	
	
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/system/click", &m_handles[ALVR_INPUT_SYSTEM_CLICK]);
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/application_menu/click", &m_handles[ALVR_INPUT_APPLICATION_MENU_CLICK]);
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/grip/click", &m_handles[ALVR_INPUT_GRIP_CLICK]);
	//vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/grip/value", &m_handles[ALVR_INPUT_GRIP_VALUE], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/grip/touch", &m_handles[ALVR_INPUT_GRIP_TOUCH]);
	//
	//if (!m_isLeftHand) {
	//	// A,B for right hand.
	//	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/a/click", &m_handles[ALVR_INPUT_A_CLICK]);
	//	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/a/touch", &m_handles[ALVR_INPUT_A_TOUCH]);
	//	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/b/click", &m_handles[ALVR_INPUT_B_CLICK]);
	//	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/b/touch", &m_handles[ALVR_INPUT_B_TOUCH]);
	//
	//	vr::VRDriverInput()->CreateSkeletonComponent(m_ulPropertyContainer, "/input/skeleton/right", "/skeleton/hand/right", "/pose/raw", vr::EVRSkeletalTrackingLevel::VRSkeletalTracking_Full, nullptr, 0U, &m_compSkeleton);
	//}
	//else {
	//	// X,Y for left hand.
	//	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/x/click", &m_handles[ALVR_INPUT_X_CLICK]);
	//	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/x/touch", &m_handles[ALVR_INPUT_X_TOUCH]);
	//	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/y/click", &m_handles[ALVR_INPUT_Y_CLICK]);
	//	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/y/touch", &m_handles[ALVR_INPUT_Y_TOUCH]);
	//
	//	vr::VRDriverInput()->CreateSkeletonComponent(m_ulPropertyContainer, "/input/skeleton/left", "/skeleton/hand/left", "/pose/raw", vr::EVRSkeletalTrackingLevel::VRSkeletalTracking_Full, nullptr, 0U, &m_compSkeleton);
	//}
	//
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/joystick/click", &m_handles[ALVR_INPUT_JOYSTICK_CLICK]);
	//vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/joystick/x", &m_handles[ALVR_INPUT_JOYSTICK_X], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedTwoSided);
	//vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/joystick/y", &m_handles[ALVR_INPUT_JOYSTICK_Y], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedTwoSided);
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/joystick/touch", &m_handles[ALVR_INPUT_JOYSTICK_TOUCH]);
	//
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/back/click", &m_handles[ALVR_INPUT_BACK_CLICK]);
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/guide/click", &m_handles[ALVR_INPUT_GUIDE_CLICK]);
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/start/click", &m_handles[ALVR_INPUT_START_CLICK]);
	//
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/trigger/click", &m_handles[ALVR_INPUT_TRIGGER_CLICK]);
	//vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/trigger/value", &m_handles[ALVR_INPUT_TRIGGER_VALUE], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	//vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/trigger/touch", &m_handles[ALVR_INPUT_TRIGGER_TOUCH]);
	//
	//vr::VRDriverInput()->CreateHapticComponent(m_ulPropertyContainer, "/output/haptic", &m_compHaptic);


	//from leap

	//m_unObjectId = unObjectId;
	//vr::CVRPropertyHelpers* l_vrProperties = vr::VRProperties();
	//m_ulPropertyContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_unObjectId);
	//
	//l_vrProperties->SetBoolProperty(m_ulPropertyContainer, vr::Prop_WillDriftInYaw_Bool, false);
	//l_vrProperties->SetBoolProperty(m_ulPropertyContainer, vr::Prop_DeviceIsWireless_Bool, false);
	//l_vrProperties->SetInt32Property(m_ulPropertyContainer, vr::Prop_DeviceClass_Int32, vr::TrackedDeviceClass_Controller);
	//l_vrProperties->SetInt32Property(m_ulPropertyContainer, vr::Prop_ControllerRoleHint_Int32, m_isLeftHand ? vr::TrackedControllerRole_LeftHand : vr::TrackedControllerRole_RightHand);
	//
	//// Input Properties
	//l_vrProperties->SetInt32Property(m_ulPropertyContainer, vr::Prop_Axis0Type_Int32, vr::k_eControllerAxis_TrackPad);
	//l_vrProperties->SetInt32Property(m_ulPropertyContainer, vr::Prop_Axis1Type_Int32, vr::k_eControllerAxis_Trigger);
	//	l_vrProperties->SetUint64Property(m_ulPropertyContainer, vr::Prop_SupportedButtons_Uint64,
	//		vr::ButtonMaskFromId(vr::k_EButton_System) |
	//		vr::ButtonMaskFromId(vr::k_EButton_IndexController_A) |
	//		vr::ButtonMaskFromId(vr::k_EButton_IndexController_B) |
	//		vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad) |
	//		vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Trigger)
	//	);
	//
	//// Model
	//l_vrProperties->SetStringProperty(m_ulPropertyContainer, vr::Prop_ModeLabel_String, Settings::Instance().m_controllerTrackingSystemName.c_str());
	//l_vrProperties->SetStringProperty(m_ulPropertyContainer, vr::Prop_ManufacturerName_String, "Valve"); // Or is it?
	//l_vrProperties->SetStringProperty(m_ulPropertyContainer, vr::Prop_ModelNumber_String, "LeapMotion");
	//l_vrProperties->SetStringProperty(m_ulPropertyContainer, vr::Prop_SerialNumber_String, m_isLeftHand ? (Settings::Instance().m_controllerModelNumber + " (Left Controller)").c_str() : (Settings::Instance().m_controllerModelNumber + " (Right Controller)").c_str());
	//l_vrProperties->SetUint64Property(m_ulPropertyContainer, vr::Prop_HardwareRevision_Uint64, 1515);
	//l_vrProperties->SetUint64Property(m_ulPropertyContainer, vr::Prop_FirmwareVersion_Uint64, 1515);
	//l_vrProperties->SetStringProperty(m_ulPropertyContainer, vr::Prop_RenderModelName_String, m_isLeftHand ? "valve_controller_knu_ev2_0_left" : "valve_controller_knu_ev2_0_right");
	
	//// Profile
	//l_vrProperties->SetStringProperty(m_ulPropertyContainer, vr::Prop_InputProfilePath_String, Settings::Instance().m_controllerInputProfilePath.c_str());
	
	// Inputs
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/system/click", &m_handles[ALVR_INPUT_SYSTEM_CLICK]);
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/grip/touch", &m_handles[ALVR_INPUT_GRIP_TOUCH]);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/grip/force", &m_handles[ALVR_INPUT_GRIP_FORCE], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/grip/value", &m_handles[ALVR_INPUT_GRIP_VALUE], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/trackpad/x", &m_handles[ALVR_INPUT_TRACKPAD_X], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedTwoSided);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/trackpad/y", &m_handles[ALVR_INPUT_TRACKPAD_Y], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedTwoSided);
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/trackpad/touch", &m_handles[ALVR_INPUT_TRACKPAD_TOUCH]);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/trackpad/force", &m_handles[ALVR_INPUT_TRACKPAD_FORCE], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/thumbstick/x", &m_handles[ALVR_INPUT_JOYSTICK_X], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedTwoSided);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/thumbstick/y", &m_handles[ALVR_INPUT_JOYSTICK_Y], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedTwoSided);
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/thumbstick/click", &m_handles[ALVR_INPUT_JOYSTICK_CLICK]);
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/thumbstick/touch", &m_handles[ALVR_INPUT_JOYSTICK_TOUCH]);
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/a/click", &m_handles[ALVR_INPUT_A_CLICK]);
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/a/touch", &m_handles[ALVR_INPUT_A_TOUCH]);
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/b/click", &m_handles[ALVR_INPUT_B_CLICK]);
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/b/touch", &m_handles[ALVR_INPUT_B_TOUCH]);
	vr::VRDriverInput()->CreateBooleanComponent(m_ulPropertyContainer, "/input/trigger/click", &m_handles[ALVR_INPUT_TRIGGER_CLICK]);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/trigger/value", &m_handles[ALVR_INPUT_TRIGGER_VALUE], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/finger/index", &m_handles[ALVR_INPUT_FINGER_INDEX], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/finger/middle", &m_handles[ALVR_INPUT_FINGER_MIDDLE], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/finger/ring", &m_handles[ALVR_INPUT_FINGER_RING], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	vr::VRDriverInput()->CreateScalarComponent(m_ulPropertyContainer, "/input/finger/pinky", &m_handles[ALVR_INPUT_FINGER_PINKY], vr::VRScalarType_Absolute, vr::VRScalarUnits_NormalizedOneSided);
	vr::VRDriverInput()->CreateSkeletonComponent(m_ulPropertyContainer, "/input/skeleton/left", "/skeleton/hand/left", "/pose/raw", vr::EVRSkeletalTrackingLevel::VRSkeletalTracking_Partial, nullptr, 0U, &m_compSkeleton);
	vr::VRDriverInput()->CreateSkeletonComponent(m_ulPropertyContainer, "/input/skeleton/right", "/skeleton/hand/right", "/pose/raw", vr::EVRSkeletalTrackingLevel::VRSkeletalTracking_Partial, nullptr, 0U, &m_compSkeleton);

	return vr::VRInitError_None;
}

void OvrController::Deactivate()
{
	Log(L"RemoteController::Deactivate");
	m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
}

void OvrController::EnterStandby()
{
}

void *OvrController::GetComponent(const char *pchComponentNameAndVersion)
{
	Log(L"RemoteController::GetComponent. Name=%hs", pchComponentNameAndVersion);

	return NULL;
}

 void PowerOff()
{
}

/** debug request from a client */
 void OvrController::DebugRequest(const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize)
{
	if (unResponseBufferSize >= 1)
		pchResponseBuffer[0] = 0;
}

 vr::DriverPose_t OvrController::GetPose()
{

	 Log(L"Controller%d getPose %lf %lf %lf", m_index, m_pose.vecPosition[0], m_pose.vecPosition[1], m_pose.vecPosition[2]);

	return m_pose;
}

 int OvrController::getControllerIndex() {
	 return m_index;
 }

 vr::VRInputComponentHandle_t OvrController::getHapticComponent() {
	return m_compHaptic;
}
vr::HmdQuaternion_t QuatMultiply(const vr::HmdQuaternion_t *q1, const vr::HmdQuaternion_t *q2)
{
	vr::HmdQuaternion_t result;
	result.x = q1->w*q2->x + q1->x*q2->w + q1->y*q2->z - q1->z*q2->y;
	result.y = q1->w*q2->y - q1->x*q2->z + q1->y*q2->w + q1->z*q2->x;
	result.z = q1->w*q2->z + q1->x*q2->y - q1->y*q2->x + q1->z*q2->w;
	result.w = q1->w*q2->w - q1->x*q2->x - q1->y*q2->y - q1->z*q2->z;
	return result;
}
bool OvrController::onPoseUpdate(int controllerIndex, const TrackingInfo &info) {

	if (m_unObjectId == vr::k_unTrackedDeviceIndexInvalid) {
		return false;
	}
	
	if (info.controller[controllerIndex].flags & TrackingInfo::Controller::FLAG_CONTROLLER_OCULUS_HAND) {
		//m_pose.qRotation = HmdQuaternion_Init(
		//	info.controller[controllerIndex].boneRootOrientation.w,
		//	info.controller[controllerIndex].boneRootOrientation.x,
		//	info.controller[controllerIndex].boneRootOrientation.y,
		//	info.controller[controllerIndex].boneRootOrientation.z);
		//m_pose.vecPosition[0] = info.controller[controllerIndex].boneRootPosition.x;
		//m_pose.vecPosition[1] = info.controller[controllerIndex].boneRootPosition.y;
		//m_pose.vecPosition[2] = info.controller[controllerIndex].boneRootPosition.z;

		vr::HmdQuaternion_t rootBoneRot = HmdQuaternion_Init(
			info.controller[controllerIndex].boneRootOrientation.w,
			info.controller[controllerIndex].boneRootOrientation.x,
			info.controller[controllerIndex].boneRootOrientation.y,
			info.controller[controllerIndex].boneRootOrientation.z);
		vr::HmdQuaternion_t wristBoneRot = HmdQuaternion_Init(
			info.controller[controllerIndex].boneRotations[alvrHandBone_WristRoot].w,
			info.controller[controllerIndex].boneRotations[alvrHandBone_WristRoot].x,
			info.controller[controllerIndex].boneRotations[alvrHandBone_WristRoot].y,
			info.controller[controllerIndex].boneRotations[alvrHandBone_WristRoot].z);
		//vr::HmdQuaternion_t middleBoneRot = HmdQuaternion_Init(
		//	info.controller[controllerIndex].boneRotations[alvrHandBone_Middle1].w,
		//	info.controller[controllerIndex].boneRotations[alvrHandBone_Middle1].x,
		//	info.controller[controllerIndex].boneRotations[alvrHandBone_Middle1].y,
		//	info.controller[controllerIndex].boneRotations[alvrHandBone_Middle1].z);
		double rootBonePos[3];
		double wristBonePos[3];
		//double middleBonePos[3];
		rootBonePos[0] = info.controller[controllerIndex].boneRootPosition.x;
		rootBonePos[1] = info.controller[controllerIndex].boneRootPosition.y;
		rootBonePos[2] = info.controller[controllerIndex].boneRootPosition.z;
		wristBonePos[0] = info.controller[controllerIndex].bonePositionsBase[alvrHandBone_WristRoot].x;
		wristBonePos[1] = info.controller[controllerIndex].bonePositionsBase[alvrHandBone_WristRoot].y;
		wristBonePos[2] = info.controller[controllerIndex].bonePositionsBase[alvrHandBone_WristRoot].z;
		//middleBonePos[0] = info.controller[controllerIndex].bonePositionsBase[alvrHandBone_Middle1].x;
		//middleBonePos[1] = info.controller[controllerIndex].bonePositionsBase[alvrHandBone_Middle1].y;
		//middleBonePos[2] = info.controller[controllerIndex].bonePositionsBase[alvrHandBone_Middle1].z;

		wristBonePos[0] = rootBonePos[0] + wristBonePos[0] * (-rootBoneRot.x) / rootBoneRot.w;
		wristBonePos[1] = rootBonePos[1] + wristBonePos[1] * (-rootBoneRot.z) / rootBoneRot.w;
		wristBonePos[2] = rootBonePos[2] + wristBonePos[2] * (-rootBoneRot.x) / rootBoneRot.w;
		wristBoneRot = QuatMultiply(&rootBoneRot, &wristBoneRot);

		//middleBonePos[0] = wristBonePos[0] + middleBonePos[0] * (-wristBoneRot.x) / wristBoneRot.w;
		//middleBonePos[1] = wristBonePos[1] + middleBonePos[1] * (-wristBoneRot.z) / wristBoneRot.w;
		//middleBonePos[2] = wristBonePos[2] + middleBonePos[2] * (-wristBoneRot.x) / wristBoneRot.w;
		//middleBoneRot = QuatMultiply(&wristBoneRot, &middleBoneRot);

		m_pose.qRotation = wristBoneRot;
		m_pose.vecPosition[0] = wristBonePos[0];
		m_pose.vecPosition[1] = wristBonePos[1];
		m_pose.vecPosition[2] = wristBonePos[2];
	}
	else {
		m_pose.qRotation = HmdQuaternion_Init(
			info.controller[controllerIndex].orientation.w,
			info.controller[controllerIndex].orientation.x,
			info.controller[controllerIndex].orientation.y,
			info.controller[controllerIndex].orientation.z);
		m_pose.vecPosition[0] = info.controller[controllerIndex].position.x;
		m_pose.vecPosition[1] = info.controller[controllerIndex].position.y;
		m_pose.vecPosition[2] = info.controller[controllerIndex].position.z;
	}


	

	m_pose.vecVelocity[0] = info.controller[controllerIndex].linearVelocity.x;
	m_pose.vecVelocity[1] = info.controller[controllerIndex].linearVelocity.y;
	m_pose.vecVelocity[2] = info.controller[controllerIndex].linearVelocity.z;
	//m_pose.vecAcceleration[0] = info.controller[controllerIndex].linearAcceleration.x;
	//m_pose.vecAcceleration[1] = info.controller[controllerIndex].linearAcceleration.y;
	//m_pose.vecAcceleration[2] = info.controller[controllerIndex].linearAcceleration.z;
	m_pose.vecAngularVelocity[0] = info.controller[controllerIndex].angularVelocity.x;
	m_pose.vecAngularVelocity[1] = info.controller[controllerIndex].angularVelocity.y;
	m_pose.vecAngularVelocity[2] = info.controller[controllerIndex].angularVelocity.z;
	//m_pose.vecAngularAcceleration[0] = info.controller[controllerIndex].angularAcceleration.x;
	//m_pose.vecAngularAcceleration[1] = info.controller[controllerIndex].angularAcceleration.y;
	//m_pose.vecAngularAcceleration[2] = info.controller[controllerIndex].angularAcceleration.z;
	
	
	
	//correct direction of velocities
	vr::HmdVector3d_t angVel;
	angVel.v[0] = m_pose.vecAngularVelocity[0];
	angVel.v[1] = m_pose.vecAngularVelocity[1];
	angVel.v[2] = m_pose.vecAngularVelocity[2];
	vr::HmdVector3d_t angVelRes = vrmath::quaternionRotateVector(m_pose.qRotation, angVel, true);
	m_pose.vecAngularVelocity[0] = angVelRes.v[0];
	m_pose.vecAngularVelocity[1] = angVelRes.v[1];
	m_pose.vecAngularVelocity[2] = angVelRes.v[2];
	



	/*
	vr::HmdVector3d_t vel;
	vel.v[0] = m_pose.vecVelocity[0];
	vel.v[1] = m_pose.vecVelocity[1];
	vel.v[2] = m_pose.vecVelocity[2];
	vr::HmdVector3d_t velRes = vrmath::quaternionRotateVector(m_pose.qRotation, vel, true);
	m_pose.vecVelocity[0] = velRes.v[0];
	m_pose.vecVelocity[1] = velRes.v[1];
	m_pose.vecVelocity[2] = velRes.v[2];
	*/
	

	Log(L"CONTROLLER %d %f,%f,%f - %f,%f,%f", m_index, m_pose.vecVelocity[0], m_pose.vecVelocity[1], m_pose.vecVelocity[2], m_pose.vecAngularVelocity[0], m_pose.vecAngularVelocity[1], m_pose.vecAngularVelocity[2]);
	
	

	/*
	double rotation[3] = { 0.0, 0.0, 36 * M_PI / 180 };
	m_pose.qDriverFromHeadRotation = EulerAngleToQuaternion(rotation);
	m_pose.vecDriverFromHeadTranslation[1] = 0.031153;
	m_pose.vecDriverFromHeadTranslation[2] = -0.042878;

	

	//double r[3] = { 0, -0.031153 ,0.042878 };
	double r[3] = { 0, 0 ,-0.053 };
	double v1[3] = { m_pose.vecVelocity[0], m_pose.vecVelocity[1], m_pose.vecVelocity[2] };
	double w[3] = { m_pose.vecAngularVelocity[0], m_pose.vecAngularVelocity[1], m_pose.vecAngularVelocity[2] };

	double tmp[3] = { 0, 0 ,0 };
	tmp[0] = (w[1] * r[2]) - (w[2] * r[1]);
	tmp[1] = (w[2] * r[0]) - (w[0] * r[2]);
	tmp[2] = (w[0] * r[1]) - (w[1] * r[0]);



	m_pose.vecVelocity[0] = m_pose.vecVelocity[0] + tmp[0];
	m_pose.vecVelocity[1] = m_pose.vecVelocity[1] + tmp[1];
	m_pose.vecVelocity[2] = m_pose.vecVelocity[2] + tmp[2];
	*/
	

	m_pose.poseTimeOffset = Settings::Instance().m_controllerPoseOffset;

	   

	auto& c = info.controller[controllerIndex];
	Log(L"Controller%d %d %lu: %08llX %08X %f:%f", m_index,controllerIndex, (unsigned long)m_unObjectId, c.buttons, c.flags, c.trackpadPosition.x, c.trackpadPosition.y);

	if (c.flags & TrackingInfo::Controller::FLAG_CONTROLLER_OCULUS_HAND) {

		//if (!m_isLeftHand) {
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_A_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_IndexPinching) != 0, 0.0);
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_A_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_IndexPinching) != 0, 0.0);
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_B_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_MiddlePinching) != 0, 0.0);
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_B_TOUCH], (c.inputStateStatus & alvrInputStateHandStatus_MiddlePinching) != 0, 0.0);
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_SYSTEM_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_RingPinching) != 0, 0.0);
		//}
		//else {
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_A_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_IndexPinching) != 0, 0.0);
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_A_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_IndexPinching) != 0, 0.0);
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_B_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_MiddlePinching) != 0, 0.0);
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_B_TOUCH], (c.inputStateStatus & alvrInputStateHandStatus_MiddlePinching) != 0, 0.0);
		//	vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_SYSTEM_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_RingPinching) != 0, 0.0);
		//}
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_SYSTEM_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_RingPinching) != 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_GRIP_TOUCH], false, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_GRIP_VALUE], 0, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_TRACKPAD_X], 0, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_TRACKPAD_Y], 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_TRACKPAD_TOUCH], false, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_JOYSTICK_X], 0, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_JOYSTICK_Y], 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_JOYSTICK_CLICK], false, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_JOYSTICK_TOUCH], false, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_A_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_IndexPinching) != 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_A_TOUCH], (c.inputStateStatus & alvrInputStateHandStatus_IndexPinching) != 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_B_CLICK], (c.inputStateStatus & alvrInputStateHandStatus_MiddlePinching) != 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_B_TOUCH], (c.inputStateStatus & alvrInputStateHandStatus_MiddlePinching) != 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_TRIGGER_CLICK], false, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_TRIGGER_VALUE], 0, 0.0);
		//Hand
		for (size_t i = 0U; i < HSB_Count; i++) m_boneTransform[i] = handRestPose[i];
#define COPY4(a,b) do{b.w=a.w;b.x=a.x;b.y=a.y;b.z=a.z;}while(0)
#define COPY4M(a,b,c) do{b.w=a.w*c;b.x=a.x*c;b.y=a.y*c;b.z=a.z*c;}while(0)
#define ADD4(a,b) do{b.w+=a.w;b.x+=a.x;b.y+=a.y;b.z+=a.z;}while(0)
#define COPY3(a,b) do{b.v[0]=a.x;b.v[1]=a.y;b.v[2]=a.z;}while(0)
#define COPY3M(a,b,c) do{b.v[0]=a.x*c;b.v[1]=a.y*c;b.v[2]=a.z*c;}while(0)
#define SIZE4(b) (sqrt(b.v[0]*b.v[0]+b.v[1]*b.v[1]+b.v[2]*b.v[2]))
#define APPSIZE4(a,b,c) do{a.v[0]*=b/c;a.v[1]*=b/c;a.v[2]*=b/c;}while(0)

		//COPY4(c.boneRootOrientation, m_boneTransform[HSB_Root].orientation);
		//COPY4(c.orientation, m_boneTransform[HSB_Root].orientation);
		COPY4(m_pose.qRotation, m_boneTransform[HSB_Root].orientation);
		//COPY4(c.boneRotations[alvrHandBone_WristRoot], m_boneTransform[HSB_Wrist].orientation);
		COPY4(c.boneRotations[alvrHandBone_Thumb0], m_boneTransform[HSB_Thumb0].orientation);
		COPY4(c.boneRotations[alvrHandBone_Thumb1], m_boneTransform[HSB_Thumb1].orientation);
		COPY4(c.boneRotations[alvrHandBone_Thumb2], m_boneTransform[HSB_Thumb2].orientation);
		COPY4(c.boneRotations[alvrHandBone_Thumb3], m_boneTransform[HSB_Thumb3].orientation);
		//COPY4M(c.boneRotations[alvrHandBone_Index1], m_boneTransform[HSB_IndexFinger0].orientation, 0.5);
		//COPY4M(c.boneRotations[alvrHandBone_Index1], m_boneTransform[HSB_IndexFinger1].orientation, 0.5);
		COPY4(c.boneRotations[alvrHandBone_Index1], m_boneTransform[HSB_IndexFinger1].orientation);
		COPY4(c.boneRotations[alvrHandBone_Index2], m_boneTransform[HSB_IndexFinger2].orientation);
		COPY4(c.boneRotations[alvrHandBone_Index3], m_boneTransform[HSB_IndexFinger3].orientation);
		//COPY4M(c.boneRotations[alvrHandBone_Middle1], m_boneTransform[HSB_MiddleFinger0].orientation, 0.5);
		//COPY4M(c.boneRotations[alvrHandBone_Middle1], m_boneTransform[HSB_MiddleFinger1].orientation, 0.5);
		COPY4(c.boneRotations[alvrHandBone_Middle1], m_boneTransform[HSB_MiddleFinger1].orientation);
		COPY4(c.boneRotations[alvrHandBone_Middle2], m_boneTransform[HSB_MiddleFinger2].orientation);
		COPY4(c.boneRotations[alvrHandBone_Middle3], m_boneTransform[HSB_MiddleFinger3].orientation);
		//COPY4M(c.boneRotations[alvrHandBone_Ring1], m_boneTransform[HSB_RingFinger0].orientation, 0.5);
		//COPY4M(c.boneRotations[alvrHandBone_Ring1], m_boneTransform[HSB_RingFinger1].orientation, 0.5);
		COPY4(c.boneRotations[alvrHandBone_Ring1], m_boneTransform[HSB_RingFinger1].orientation);
		COPY4(c.boneRotations[alvrHandBone_Ring2], m_boneTransform[HSB_RingFinger2].orientation);
		COPY4(c.boneRotations[alvrHandBone_Ring3], m_boneTransform[HSB_RingFinger3].orientation);
		COPY4(c.boneRotations[alvrHandBone_Pinky0], m_boneTransform[HSB_PinkyFinger0].orientation);
		COPY4(c.boneRotations[alvrHandBone_Pinky1], m_boneTransform[HSB_PinkyFinger1].orientation);
		COPY4(c.boneRotations[alvrHandBone_Pinky2], m_boneTransform[HSB_PinkyFinger2].orientation);
		COPY4(c.boneRotations[alvrHandBone_Pinky3], m_boneTransform[HSB_PinkyFinger3].orientation);

		//COPY3(c.boneRootPosition, m_boneTransform[HSB_Root].position);
		//COPY3(c.position, m_boneTransform[HSB_Root].position);
		m_boneTransform[HSB_Root].position.v[0] = m_pose.vecPosition[0];
		m_boneTransform[HSB_Root].position.v[1] = m_pose.vecPosition[1];
		m_boneTransform[HSB_Root].position.v[2] = m_pose.vecPosition[2];
		//COPY3(c.bonePositionsBase[alvrHandBone_WristRoot], m_boneTransform[HSB_Wrist].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Thumb0], m_boneTransform[HSB_Thumb0].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Thumb1], m_boneTransform[HSB_Thumb1].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Thumb2], m_boneTransform[HSB_Thumb2].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Thumb3], m_boneTransform[HSB_Thumb3].position);
		//COPY3M(c.bonePositionsBase[alvrHandBone_Index1], m_boneTransform[HSB_IndexFinger0].position, 0.5);
		//COPY3M(c.bonePositionsBase[alvrHandBone_Index1], m_boneTransform[HSB_IndexFinger1].position, 0.5);
		COPY3(c.bonePositionsBase[alvrHandBone_Index1], m_boneTransform[HSB_IndexFinger1].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Index2], m_boneTransform[HSB_IndexFinger2].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Index3], m_boneTransform[HSB_IndexFinger3].position);
		//COPY3M(c.bonePositionsBase[alvrHandBone_Middle1], m_boneTransform[HSB_MiddleFinger0].position, 0.5);
		//COPY3M(c.bonePositionsBase[alvrHandBone_Middle1], m_boneTransform[HSB_MiddleFinger1].position, 0.5);
		COPY3(c.bonePositionsBase[alvrHandBone_Middle1], m_boneTransform[HSB_MiddleFinger1].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Middle2], m_boneTransform[HSB_MiddleFinger2].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Middle3], m_boneTransform[HSB_MiddleFinger3].position);
		//COPY3M(c.bonePositionsBase[alvrHandBone_Ring1], m_boneTransform[HSB_RingFinger0].position, 0.5);
		//COPY3M(c.bonePositionsBase[alvrHandBone_Ring1], m_boneTransform[HSB_RingFinger1].position, 0.5);
		COPY3(c.bonePositionsBase[alvrHandBone_Ring1], m_boneTransform[HSB_RingFinger1].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Ring2], m_boneTransform[HSB_RingFinger2].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Ring3], m_boneTransform[HSB_RingFinger3].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Pinky0], m_boneTransform[HSB_PinkyFinger0].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Pinky1], m_boneTransform[HSB_PinkyFinger1].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Pinky2], m_boneTransform[HSB_PinkyFinger2].position);
		COPY3(c.bonePositionsBase[alvrHandBone_Pinky3], m_boneTransform[HSB_PinkyFinger3].position);

		vr::VRDriverInput()->UpdateSkeletonComponent(m_compSkeleton, vr::VRSkeletalMotionRange_WithController, m_boneTransform, HSB_Count);
		vr::VRDriverInput()->UpdateSkeletonComponent(m_compSkeleton, vr::VRSkeletalMotionRange_WithoutController, m_boneTransform, HSB_Count);

		//vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_FINGER_INDEX], c.boneRotations[alvrHandBone_Index1].z / 3.14 * 90 + 90, 0.0);
		//vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_FINGER_MIDDLE], c.boneRotations[alvrHandBone_Middle1].z / 3.14 * 90 + 90, 0.0);
		//vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_FINGER_RING], c.boneRotations[alvrHandBone_Ring1].z / 3.14 * 90 + 90, 0.0);
		//vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_FINGER_PINKY], c.boneRotations[alvrHandBone_Pinky1].z / 3.14 * 90 + 90, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_FINGER_INDEX], c.boneRotations[alvrHandBone_Index1].z, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_FINGER_MIDDLE], c.boneRotations[alvrHandBone_Middle1].z, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_FINGER_RING], c.boneRotations[alvrHandBone_Ring1].z, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_FINGER_PINKY], c.boneRotations[alvrHandBone_Pinky1].z, 0.0);

		vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_unObjectId, m_pose, sizeof(vr::DriverPose_t));
	}
	else {

		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_SYSTEM_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_SYSTEM_CLICK)) != 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_APPLICATION_MENU_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_APPLICATION_MENU_CLICK)) != 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_GRIP_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_GRIP_CLICK)) != 0, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_GRIP_VALUE], c.gripValue, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_GRIP_TOUCH], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_GRIP_TOUCH)) != 0, 0.0);


		if (!m_isLeftHand) {
			// A,B for right hand.
			vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_A_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_A_CLICK)) != 0, 0.0);
			vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_A_TOUCH], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_A_TOUCH)) != 0, 0.0);
			vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_B_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_B_CLICK)) != 0, 0.0);
			vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_B_TOUCH], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_B_TOUCH)) != 0, 0.0);

		}
		else {
			// X,Y for left hand.
			vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_X_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_X_CLICK)) != 0, 0.0);
			vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_X_TOUCH], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_X_TOUCH)) != 0, 0.0);
			vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_Y_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_Y_CLICK)) != 0, 0.0);
			vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_Y_TOUCH], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_Y_TOUCH)) != 0, 0.0);
		}

		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_JOYSTICK_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_JOYSTICK_CLICK)) != 0, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_JOYSTICK_X], c.trackpadPosition.x, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_JOYSTICK_Y], c.trackpadPosition.y, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_JOYSTICK_TOUCH], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_JOYSTICK_TOUCH)) != 0, 0.0);


		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_BACK_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_BACK_CLICK)) != 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_GUIDE_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_GUIDE_CLICK)) != 0, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_START_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_START_CLICK)) != 0, 0.0);

		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_TRIGGER_CLICK], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_TRIGGER_CLICK)) != 0, 0.0);
		vr::VRDriverInput()->UpdateScalarComponent(m_handles[ALVR_INPUT_TRIGGER_VALUE], c.triggerValue, 0.0);
		vr::VRDriverInput()->UpdateBooleanComponent(m_handles[ALVR_INPUT_TRIGGER_TOUCH], (c.buttons & ALVR_BUTTON_FLAG(ALVR_INPUT_TRIGGER_TOUCH)) != 0, 0.0);

		// Battery
		vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, vr::Prop_DeviceBatteryPercentage_Float, c.batteryPercentRemaining / 100.0f);

		vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_unObjectId, m_pose, sizeof(vr::DriverPose_t));
	}
	return false;
}

std::string OvrController::GetSerialNumber() {
	char str[100];
	snprintf(str, sizeof(str), "_%s", m_index == 0 ? "Left" : "Right");
	return Settings::Instance().m_controllerSerialNumber + str;
}