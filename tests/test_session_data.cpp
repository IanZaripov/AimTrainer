#include <gtest/gtest.h>
#include "SessionData.h"

TEST(SessionData, StartsInactive) {
    SessionData s;
    EXPECT_FALSE(s.IsActive());
    EXPECT_EQ(s.GetExitReason(), GameExitReason::None);
}

TEST(SessionData, StartActivatesSession) {
    SessionData s;
    s.Start();
    EXPECT_TRUE(s.IsActive());
}

TEST(SessionData, RegisterHitIncrementsBothCounters) {
    SessionData s;
    s.RegisterHit();
    EXPECT_EQ(s.GetHits(), 1);
    EXPECT_EQ(s.GetPoppedCount(), 1);
}

TEST(SessionData, RegisterShotDoesNotAffectHits) {
    SessionData s;
    s.RegisterShot();
    EXPECT_EQ(s.GetShotsFired(), 1);
    EXPECT_EQ(s.GetHits(), 0);
}

TEST(SessionData, ResetClearsEverything) {
    SessionData s;
    s.Start();
    s.RegisterHit();
    s.RegisterShot();
    s.AddSpawned(5);
    s.Reset();

    EXPECT_FALSE(s.IsActive());
    EXPECT_EQ(s.GetHits(), 0);
    EXPECT_EQ(s.GetPoppedCount(), 0);
    EXPECT_EQ(s.GetShotsFired(), 0);
    EXPECT_EQ(s.GetSpawnedBalls(), 0);
}

TEST(SessionData, EndSetsExitReason) {
    SessionData s;
    s.Start();
    s.End(GameExitReason::TimeExpired);
    EXPECT_FALSE(s.IsActive());
    EXPECT_EQ(s.GetExitReason(), GameExitReason::TimeExpired);
}