// BLACK OCEAN - Example Automation Test
#include "Misc/AutomationTest.h"
#include "EconomySubsystem.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlackOceanEconomyBudgetTest, "BlackOcean.Economy.BudgetAllocation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FBlackOceanEconomyBudgetTest::RunTest(const FString& Parameters)
{
	UEconomySubsystem* Economy = NewObject<UEconomySubsystem>();
	Economy->SetAnnualBudget(1000.0f);

	TestTrue(TEXT("Allocating within budget should succeed"),
		Economy->AllocateBudget(EBudgetCategory::Navy, 400.0f));
	TestTrue(TEXT("Allocating remaining budget should succeed"),
		Economy->AllocateBudget(EBudgetCategory::Research, 500.0f));
	TestFalse(TEXT("Allocating beyond remaining budget should fail"),
		Economy->AllocateBudget(EBudgetCategory::Industry, 200.0f));

	TestEqual(TEXT("Remaining unallocated should be 100"), Economy->GetRemainingUnallocated(), 100.0f);

	TestTrue(TEXT("Spending within a category balance should succeed"),
		Economy->SpendFromCategory(EBudgetCategory::Navy, 150.0f));
	TestEqual(TEXT("Navy balance should reflect the spend"),
		Economy->GetCategoryBalance(EBudgetCategory::Navy), 250.0f);

	return true;
}
