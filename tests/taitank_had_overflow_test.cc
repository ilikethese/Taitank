/*
 *
 * Tencent is pleased to support the open source community by making Taitank available. 
 * Copyright (C) 2021 THL A29 Limited, a Tencent company.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the “License”);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http:// www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations
 * under the License.
 *
 */

#include "taitank.h"

#include "gtest.h"

using namespace taitank;
using namespace ::testing;

class TAITANK_TEST_HAD_OVERFLOW : public Test {
 protected:
  TAITANK_TEST_HAD_OVERFLOW() {
    root = TaitankNodeCreate();
    set_taitank_node_style_width(root, 200);
    set_taitank_node_style_height(root, 100);
    set_taitank_node_style_flex_direction(root, FLEX_DIRECTION_COLUMN);
    set_taitank_node_style_flex_wrap(root, FLEX_NO_WRAP);
  }

  ~TAITANK_TEST_HAD_OVERFLOW() { TaitankNodeFreeRecursive(root); }

  TaitankNodeRef root;
};

TEST_F(TAITANK_TEST_HAD_OVERFLOW, children_overflow_no_wrap_and_no_flex_children) {
  const TaitankNodeRef child0 = TaitankNodeCreate();
  set_taitank_node_style_width(child0, 80);
  set_taitank_node_style_height(child0, 40);
  set_taitank_node_style_margin(child0, CSS_TOP, 10);
  set_taitank_node_style_margin(child0, CSS_BOTTOM, 15);
  TaitankNodeInsertChild(root, child0, 0);
  const TaitankNodeRef child1 = TaitankNodeCreate();
  set_taitank_node_style_width(child1, 80);
  set_taitank_node_style_height(child1, 40);
  set_taitank_node_style_margin(child1, CSS_BOTTOM, 5);
  TaitankNodeInsertChild(root, child1, 1);

  TaitankNodeDoLayout(root, 200, 100);

  ASSERT_TRUE(get_taitank_node_layout_had_overflow(root));
}

TEST_F(TAITANK_TEST_HAD_OVERFLOW, spacing_overflow_no_wrap_and_no_flex_children) {
  const TaitankNodeRef child0 = TaitankNodeCreate();
  set_taitank_node_style_width(child0, 80);
  set_taitank_node_style_height(child0, 40);
  set_taitank_node_style_margin(child0, CSS_TOP, 10);
  set_taitank_node_style_margin(child0, CSS_BOTTOM, 10);
  TaitankNodeInsertChild(root, child0, 0);
  const TaitankNodeRef child1 = TaitankNodeCreate();
  set_taitank_node_style_width(child1, 80);
  set_taitank_node_style_height(child1, 40);
  set_taitank_node_style_margin(child1, CSS_BOTTOM, 5);
  TaitankNodeInsertChild(root, child1, 1);

  TaitankNodeDoLayout(root, 200, 100);

  ASSERT_TRUE(get_taitank_node_layout_had_overflow(root));
}

TEST_F(TAITANK_TEST_HAD_OVERFLOW, no_overflow_no_wrap_and_flex_children) {
  const TaitankNodeRef child0 = TaitankNodeCreate();
  set_taitank_node_style_width(child0, 80);
  set_taitank_node_style_height(child0, 40);
  set_taitank_node_style_margin(child0, CSS_TOP, 10);
  set_taitank_node_style_margin(child0, CSS_BOTTOM, 10);
  TaitankNodeInsertChild(root, child0, 0);
  const TaitankNodeRef child1 = TaitankNodeCreate();
  set_taitank_node_style_width(child1, 80);
  set_taitank_node_style_height(child1, 40);
  set_taitank_node_style_margin(child1, CSS_BOTTOM, 5);
  set_taitank_node_style_flex_shrink(child1, 1);
  TaitankNodeInsertChild(root, child1, 1);

  TaitankNodeDoLayout(root, 200, 100);

  ASSERT_FALSE(get_taitank_node_layout_had_overflow(root));
}

TEST_F(TAITANK_TEST_HAD_OVERFLOW, hadOverflow_gets_reset_if_not_logger_valid) {
  const TaitankNodeRef child0 = TaitankNodeCreate();
  set_taitank_node_style_width(child0, 80);
  set_taitank_node_style_height(child0, 40);
  set_taitank_node_style_margin(child0, CSS_TOP, 10);
  set_taitank_node_style_margin(child0, CSS_BOTTOM, 10);
  TaitankNodeInsertChild(root, child0, 0);
  const TaitankNodeRef child1 = TaitankNodeCreate();
  set_taitank_node_style_width(child1, 80);
  set_taitank_node_style_height(child1, 40);
  set_taitank_node_style_margin(child1, CSS_BOTTOM, 5);
  TaitankNodeInsertChild(root, child1, 1);

  TaitankNodeDoLayout(root, 200, 100);

  ASSERT_TRUE(get_taitank_node_layout_had_overflow(root));

  set_taitank_node_style_flex_shrink(child1, 1);

  TaitankNodeDoLayout(root, 200, 100);
  ASSERT_FALSE(get_taitank_node_layout_had_overflow(root));
}

TEST_F(TAITANK_TEST_HAD_OVERFLOW, spacing_overflow_in_nested_nodes) {
  const TaitankNodeRef child0 = TaitankNodeCreate();
  set_taitank_node_style_width(child0, 80);
  set_taitank_node_style_height(child0, 40);
  set_taitank_node_style_margin(child0, CSS_TOP, 10);
  set_taitank_node_style_margin(child0, CSS_BOTTOM, 10);
  TaitankNodeInsertChild(root, child0, 0);
  const TaitankNodeRef child1 = TaitankNodeCreate();
  set_taitank_node_style_width(child1, 80);
  set_taitank_node_style_height(child1, 40);
  TaitankNodeInsertChild(root, child1, 1);
  const TaitankNodeRef child1_1 = TaitankNodeCreate();
  set_taitank_node_style_width(child1_1, 80);
  set_taitank_node_style_height(child1_1, 40);
  set_taitank_node_style_margin(child1_1, CSS_BOTTOM, 5);
  TaitankNodeInsertChild(child1, child1_1, 0);

  TaitankNodeDoLayout(root, 200, 100);

  ASSERT_TRUE(get_taitank_node_layout_had_overflow(root));
}
