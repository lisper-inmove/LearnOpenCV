# ============================================
# LearnOpenCV_Test 测试模块配置
# 此文件由 scripts/generate_test_rules.sh 自动生成
# 请勿手动编辑，运行脚本即可更新
# ============================================

TEST_EXECUTABLE := LearnOpenCV_Test
TEST_SRC_DIR := tests

# 构建目录检测
ifneq ($(wildcard build-Debug),)
    BUILD_DIR_DEBUG_ACTUAL := build-Debug
else
    BUILD_DIR_DEBUG_ACTUAL := build-debug
endif

TEST_EXEC_DEBUG := $(firstword $(wildcard $(BUILD_DIR_DEBUG_ACTUAL)/bin/$(TEST_EXECUTABLE)) $(wildcard $(BUILD_DIR_DEBUG_ACTUAL)/$(TEST_EXECUTABLE)))

# ============================================
# 构建检查
# ============================================

build-debug-check:
	@if [ ! -f "$(TEST_EXEC_DEBUG)" ]; then \
		echo "Building Debug version..."; \
		$(MAKE) debug; \
	fi

# ============================================
# AppendX_Qt_Support 测试规则
# ============================================

.PHONY: AppendX_Qt_Support
AppendX_Qt_Support: build-debug-check
	@echo "========================================"
	@echo "Running all tests in AppendX_Qt_Support.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*QtSupportTest*"

.PHONY: AppendX_Qt_Support.QtSupportTest
AppendX_Qt_Support.QtSupportTest: build-debug-check
	@echo "Running QtSupportTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*QtSupportTest*"


# ============================================
# CH1_basic_operation 测试规则
# ============================================

.PHONY: CH1_basic_operation
CH1_basic_operation: build-debug-check
	@echo "========================================"
	@echo "Running all tests in CH1_basic_operation.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*NamedWindowTest*:*ReadWriteTest*:*OpenVideo*"

.PHONY: CH1_basic_operation.NamedWindowTest
CH1_basic_operation.NamedWindowTest: build-debug-check
	@echo "Running NamedWindowTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*NamedWindowTest*"

.PHONY: CH1_basic_operation.ReadWriteTest
CH1_basic_operation.ReadWriteTest: build-debug-check
	@echo "Running ReadWriteTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ReadWriteTest*"

.PHONY: CH1_basic_operation.OpenVideo
CH1_basic_operation.OpenVideo: build-debug-check
	@echo "Running OpenVideo..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*OpenVideo*"


# ============================================
# CH2_basic_mat 测试规则
# ============================================

.PHONY: CH2_basic_mat
CH2_basic_mat: build-debug-check
	@echo "========================================"
	@echo "Running all tests in CH2_basic_mat.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*BasicMat*:*IteratorMat*:*BitOperateTest*:*ImageTypeAndChannelTest*:*CVTColorTest*:*ChannelOperateTest*:*ChannelOperateMixTest*"

.PHONY: CH2_basic_mat.BasicMat
CH2_basic_mat.BasicMat: build-debug-check
	@echo "Running BasicMat..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*BasicMat*"

.PHONY: CH2_basic_mat.IteratorMat
CH2_basic_mat.IteratorMat: build-debug-check
	@echo "Running IteratorMat..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*IteratorMat*"

.PHONY: CH2_basic_mat.BitOperateTest
CH2_basic_mat.BitOperateTest: build-debug-check
	@echo "Running BitOperateTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*BitOperateTest*"

.PHONY: CH2_basic_mat.ImageTypeAndChannelTest
CH2_basic_mat.ImageTypeAndChannelTest: build-debug-check
	@echo "Running ImageTypeAndChannelTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ImageTypeAndChannelTest*"

.PHONY: CH2_basic_mat.CVTColorTest
CH2_basic_mat.CVTColorTest: build-debug-check
	@echo "Running CVTColorTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*CVTColorTest*"

.PHONY: CH2_basic_mat.ChannelOperateTest
CH2_basic_mat.ChannelOperateTest: build-debug-check
	@echo "Running ChannelOperateTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ChannelOperateTest*"

.PHONY: CH2_basic_mat.ChannelOperateMixTest
CH2_basic_mat.ChannelOperateMixTest: build-debug-check
	@echo "Running ChannelOperateMixTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ChannelOperateMixTest*"


# ============================================
# CH4_histrogram 测试规则
# ============================================

.PHONY: CH4_histrogram
CH4_histrogram: build-debug-check
	@echo "========================================"
	@echo "Running all tests in CH4_histrogram.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*HistMeanTest*:*HistogramImageDisplayTest*:*EqualizehistTest*:*HistCompareTest*:*HistBackProjectTest*"

.PHONY: CH4_histrogram.HistMeanTest
CH4_histrogram.HistMeanTest: build-debug-check
	@echo "Running HistMeanTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*HistMeanTest*"

.PHONY: CH4_histrogram.HistogramImageDisplayTest
CH4_histrogram.HistogramImageDisplayTest: build-debug-check
	@echo "Running HistogramImageDisplayTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*HistogramImageDisplayTest*"

.PHONY: CH4_histrogram.EqualizehistTest
CH4_histrogram.EqualizehistTest: build-debug-check
	@echo "Running EqualizehistTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*EqualizehistTest*"

.PHONY: CH4_histrogram.HistCompareTest
CH4_histrogram.HistCompareTest: build-debug-check
	@echo "Running HistCompareTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*HistCompareTest*"

.PHONY: CH4_histrogram.HistBackProjectTest
CH4_histrogram.HistBackProjectTest: build-debug-check
	@echo "Running HistBackProjectTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*HistBackProjectTest*"


# ============================================
# CH5_convolution 测试规则
# ============================================

.PHONY: CH5_convolution
CH5_convolution: build-debug-check
	@echo "========================================"
	@echo "Running all tests in CH5_convolution.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*BlurTest*:*GaussianBlurTest*:*MedianBlurTest*:*Filter2DTest*:*VerticalBlurTest*:*HorizontalBlurTest*:*DiagonalBlurTest*:*GradientTest*:*PrewittTest*:*SobelTest*:*SobelBookTest*:*ScharrTest*:*MarginDetectTest*:*RemoveJYNoise*:*GaussianBilateralFilter*:*LaplacianTest*"

.PHONY: CH5_convolution.BlurTest
CH5_convolution.BlurTest: build-debug-check
	@echo "Running BlurTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*BlurTest*"

.PHONY: CH5_convolution.GaussianBlurTest
CH5_convolution.GaussianBlurTest: build-debug-check
	@echo "Running GaussianBlurTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*GaussianBlurTest*"

.PHONY: CH5_convolution.MedianBlurTest
CH5_convolution.MedianBlurTest: build-debug-check
	@echo "Running MedianBlurTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*MedianBlurTest*"

.PHONY: CH5_convolution.Filter2DTest
CH5_convolution.Filter2DTest: build-debug-check
	@echo "Running Filter2DTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*Filter2DTest*"

.PHONY: CH5_convolution.VerticalBlurTest
CH5_convolution.VerticalBlurTest: build-debug-check
	@echo "Running VerticalBlurTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*VerticalBlurTest*"

.PHONY: CH5_convolution.HorizontalBlurTest
CH5_convolution.HorizontalBlurTest: build-debug-check
	@echo "Running HorizontalBlurTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*HorizontalBlurTest*"

.PHONY: CH5_convolution.DiagonalBlurTest
CH5_convolution.DiagonalBlurTest: build-debug-check
	@echo "Running DiagonalBlurTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*DiagonalBlurTest*"

.PHONY: CH5_convolution.GradientTest
CH5_convolution.GradientTest: build-debug-check
	@echo "Running GradientTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*GradientTest*"

.PHONY: CH5_convolution.PrewittTest
CH5_convolution.PrewittTest: build-debug-check
	@echo "Running PrewittTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*PrewittTest*"

.PHONY: CH5_convolution.SobelTest
CH5_convolution.SobelTest: build-debug-check
	@echo "Running SobelTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*SobelTest*"

.PHONY: CH5_convolution.SobelBookTest
CH5_convolution.SobelBookTest: build-debug-check
	@echo "Running SobelBookTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*SobelBookTest*"

.PHONY: CH5_convolution.ScharrTest
CH5_convolution.ScharrTest: build-debug-check
	@echo "Running ScharrTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ScharrTest*"

.PHONY: CH5_convolution.MarginDetectTest
CH5_convolution.MarginDetectTest: build-debug-check
	@echo "Running MarginDetectTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*MarginDetectTest*"

.PHONY: CH5_convolution.RemoveJYNoise
CH5_convolution.RemoveJYNoise: build-debug-check
	@echo "Running RemoveJYNoise..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*RemoveJYNoise*"

.PHONY: CH5_convolution.GaussianBilateralFilter
CH5_convolution.GaussianBilateralFilter: build-debug-check
	@echo "Running GaussianBilateralFilter..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*GaussianBilateralFilter*"

.PHONY: CH5_convolution.LaplacianTest
CH5_convolution.LaplacianTest: build-debug-check
	@echo "Running LaplacianTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*LaplacianTest*"


# ============================================
# connective_label 测试规则
# ============================================

.PHONY: connective_label
connective_label: build-debug-check
	@echo "========================================"
	@echo "Running all tests in connective_label.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ConnectedComponentTest*:*ConnectedComponentWithStatsTest*"

.PHONY: connective_label.ConnectedComponentTest
connective_label.ConnectedComponentTest: build-debug-check
	@echo "Running ConnectedComponentTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ConnectedComponentTest*"

.PHONY: connective_label.ConnectedComponentWithStatsTest
connective_label.ConnectedComponentWithStatsTest: build-debug-check
	@echo "Running ConnectedComponentWithStatsTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ConnectedComponentWithStatsTest*"


# ============================================
# find_contour_test 测试规则
# ============================================

.PHONY: find_contour_test
find_contour_test: build-debug-check
	@echo "========================================"
	@echo "Running all tests in find_contour_test.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*FindConttourTest*:*ConttourMeasureTest*:*EllipseFitTest*:*LineFitTest*:*ContourApproxTest*:*ContourAnalysisTest*"

.PHONY: find_contour_test.FindConttourTest
find_contour_test.FindConttourTest: build-debug-check
	@echo "Running FindConttourTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*FindConttourTest*"

.PHONY: find_contour_test.ConttourMeasureTest
find_contour_test.ConttourMeasureTest: build-debug-check
	@echo "Running ConttourMeasureTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ConttourMeasureTest*"

.PHONY: find_contour_test.EllipseFitTest
find_contour_test.EllipseFitTest: build-debug-check
	@echo "Running EllipseFitTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*EllipseFitTest*"

.PHONY: find_contour_test.LineFitTest
find_contour_test.LineFitTest: build-debug-check
	@echo "Running LineFitTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*LineFitTest*"

.PHONY: find_contour_test.ContourApproxTest
find_contour_test.ContourApproxTest: build-debug-check
	@echo "Running ContourApproxTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ContourApproxTest*"

.PHONY: find_contour_test.ContourAnalysisTest
find_contour_test.ContourAnalysisTest: build-debug-check
	@echo "Running ContourAnalysisTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ContourAnalysisTest*"


# ============================================
# gradient_test 测试规则
# ============================================

.PHONY: gradient_test
gradient_test: build-debug-check
	@echo "========================================"
	@echo "Running all tests in gradient_test.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*OldGradientTest*:*OldSobelTest*:*OldScharrTest*:*OldLaplacianTest*:*OldCalculateSharpen*"

.PHONY: gradient_test.OldGradientTest
gradient_test.OldGradientTest: build-debug-check
	@echo "Running OldGradientTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*OldGradientTest*"

.PHONY: gradient_test.OldSobelTest
gradient_test.OldSobelTest: build-debug-check
	@echo "Running OldSobelTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*OldSobelTest*"

.PHONY: gradient_test.OldScharrTest
gradient_test.OldScharrTest: build-debug-check
	@echo "Running OldScharrTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*OldScharrTest*"

.PHONY: gradient_test.OldLaplacianTest
gradient_test.OldLaplacianTest: build-debug-check
	@echo "Running OldLaplacianTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*OldLaplacianTest*"

.PHONY: gradient_test.OldCalculateSharpen
gradient_test.OldCalculateSharpen: build-debug-check
	@echo "Running OldCalculateSharpen..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*OldCalculateSharpen*"


# ============================================
# noise_image_test 测试规则
# ============================================

.PHONY: noise_image_test
noise_image_test: build-debug-check
	@echo "========================================"
	@echo "Running all tests in noise_image_test.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*NoiseImageTest*:*GaussianNoiseImageTest*"

.PHONY: noise_image_test.NoiseImageTest
noise_image_test.NoiseImageTest: build-debug-check
	@echo "Running NoiseImageTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*NoiseImageTest*"

.PHONY: noise_image_test.GaussianNoiseImageTest
noise_image_test.GaussianNoiseImageTest: build-debug-check
	@echo "Running GaussianNoiseImageTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*GaussianNoiseImageTest*"



# ============================================
# 辅助功能
# ============================================

.PHONY: list-test-files
list-test-files:
	@echo "Available test files:"
	@for file in $(TEST_FILES); do echo "  - $$file"; done
	@echo ""
	@echo "Usage examples:"
	@echo "  make <test_filename>                    # Run all tests in a file"
	@echo "  make <test_filename>.<test_case>        # Run specific test case"
	@echo "  make list-all-tests                     # List all test cases"

.PHONY: list-all-tests
list-all-tests: build-debug-check
	@echo "All test cases in $(TEST_EXECUTABLE):"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_list_tests

.PHONY: test-all
test-all: build-debug-check
	@echo "Running all tests..."
	@$(TEST_EXEC_DEBUG)

# 运行匹配模式的测试
test-pattern-%: build-debug-check
	@pattern="$*"; \
	echo "Running tests matching pattern: $$pattern"; \
	$(TEST_EXEC_DEBUG) --gtest_filter="*$$pattern*"

