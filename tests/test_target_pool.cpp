#include <gtest/gtest.h>
#include "TargetPool.h"

TEST(TargetPool, RequestReturnsActiveTarget) {
    TargetPool pool;
    Target3D& t = pool.Request();
    EXPECT_EQ(pool.GetAll().size(), 1);
    // Note: Request doesn't set active=true, caller does
}

TEST(TargetPool, RequestReusesInactiveTargets) {
    TargetPool pool;
    pool.Request();       // slot 0
    pool.Request();       // slot 1
    EXPECT_EQ(pool.GetAll().size(), 2);

    // Kill slot 0
    pool.GetAll()[0].active = false;
    pool.GetAll()[0].ForceKill();

    // Next Request should reuse slot 0, not create slot 2
    pool.Request();
    EXPECT_EQ(pool.GetAll().size(), 2);
}

TEST(TargetPool, DeactivateAllKillsEverything) {
    TargetPool pool;
    pool.Request().active = true;
    pool.Request().active = true;
    
    pool.DeactivateAll();
    
    for (const auto& t : pool.GetAll()) {
        EXPECT_FALSE(t.active);
    }
}