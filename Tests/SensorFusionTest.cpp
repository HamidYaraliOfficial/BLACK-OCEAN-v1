// BLACK OCEAN - Example Automation Test
#include "Misc/AutomationTest.h"
#include "SensorFusionComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlackOceanSensorFusionTest, "BlackOcean.Sensors.Fusion",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FBlackOceanSensorFusionTest::RunTest(const FString& Parameters)
{
	USensorFusionComponent* Fusion = NewObject<USensorFusionComponent>();

	FGameTimestamp T0;
	T0.MinuteOfDay = 0;

	FMaritimeCoordinates Pos;
	Pos.GridX = 10.0;
	Pos.GridY = 10.0;

	Fusion->IngestReading(FName("Contact_A"), ESensorSourceType::RadarLike, 0.6f,
		EContactClassification::Unknown, Pos, T0);
	TestEqual(TEXT("First reading should create exactly one track"), Fusion->GetAllTracks().Num(), 1);

	// A second, corroborating high-reliability reading should raise confidence.
	const float ConfidenceBefore = Fusion->GetAllTracks()[0].Confidence;
	Fusion->IngestReading(FName("Contact_A"), ESensorSourceType::OpticalCamera, 0.9f,
		EContactClassification::Unknown, Pos, T0);
	TestTrue(TEXT("Corroborating reading should not decrease confidence"),
		Fusion->GetAllTracks()[0].Confidence >= ConfidenceBefore);

	// Aging the track far into the future with no refresh should decay it away.
	FGameTimestamp TFar;
	TFar.MinuteOfDay = 0;
	TFar.CampaignDay = 30;
	Fusion->DecayTracks(TFar, 10.0f);
	TestEqual(TEXT("Long-stale track should be dropped"), Fusion->GetAllTracks().Num(), 0);

	return true;
}
