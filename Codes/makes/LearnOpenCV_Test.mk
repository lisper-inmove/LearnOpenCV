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
	@$(TEST_EXEC_DEBUG) --gtest_filter="*QtSupportTest*:*CudaDeviceAvailableTest*:*CudaPerformanceTest*"

.PHONY: AppendX_Qt_Support.QtSupportTest
AppendX_Qt_Support.QtSupportTest: build-debug-check
	@echo "Running QtSupportTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*QtSupportTest*"

.PHONY: AppendX_Qt_Support.CudaDeviceAvailableTest
AppendX_Qt_Support.CudaDeviceAvailableTest: build-debug-check
	@echo "Running CudaDeviceAvailableTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*CudaDeviceAvailableTest*"

.PHONY: AppendX_Qt_Support.CudaPerformanceTest
AppendX_Qt_Support.CudaPerformanceTest: build-debug-check
	@echo "Running CudaPerformanceTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*CudaPerformanceTest*"


# ============================================
# CH1_basic_operation 测试规则
# ============================================

.PHONY: CH1_basic_operation
CH1_basic_operation: build-debug-check
	@echo "========================================"
	@echo "Running all tests in CH1_basic_operation.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*NamedWindowTest*:*ReadWriteTest*:*OpenVideo*:*NormalizeTest*"

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

.PHONY: CH1_basic_operation.NormalizeTest
CH1_basic_operation.NormalizeTest: build-debug-check
	@echo "Running NormalizeTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*NormalizeTest*"


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
# CH6_binary_image 测试规则
# ============================================

.PHONY: CH6_binary_image
CH6_binary_image: build-debug-check
	@echo "========================================"
	@echo "Running all tests in CH6_binary_image.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ThresholdTest*:*ThresholdCUDATest*:*OTSUMethod*:*TriangleMethod*:*AdaptiveThresholdTest*:*InRangeBinary*"

.PHONY: CH6_binary_image.ThresholdTest
CH6_binary_image.ThresholdTest: build-debug-check
	@echo "Running ThresholdTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ThresholdTest*"

.PHONY: CH6_binary_image.ThresholdCUDATest
CH6_binary_image.ThresholdCUDATest: build-debug-check
	@echo "Running ThresholdCUDATest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ThresholdCUDATest*"

.PHONY: CH6_binary_image.OTSUMethod
CH6_binary_image.OTSUMethod: build-debug-check
	@echo "Running OTSUMethod..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*OTSUMethod*"

.PHONY: CH6_binary_image.TriangleMethod
CH6_binary_image.TriangleMethod: build-debug-check
	@echo "Running TriangleMethod..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*TriangleMethod*"

.PHONY: CH6_binary_image.AdaptiveThresholdTest
CH6_binary_image.AdaptiveThresholdTest: build-debug-check
	@echo "Running AdaptiveThresholdTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*AdaptiveThresholdTest*"

.PHONY: CH6_binary_image.InRangeBinary
CH6_binary_image.InRangeBinary: build-debug-check
	@echo "Running InRangeBinary..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*InRangeBinary*"


# ============================================
# CH7_binary_analysis 测试规则
# ============================================

.PHONY: CH7_binary_analysis
CH7_binary_analysis: build-debug-check
	@echo "========================================"
	@echo "Running all tests in CH7_binary_analysis.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*BinaryMethodCompareTest*:*ConnectedComponentLabelingTest*:*FindContoursTest*:*DrawContoursTest*:*ContourMeatureTest*:*MomentsTest*:*FitAndApproxTest*:*EllipseFitTest*:*LineFitTest*:*ApproxPolyDPTest*:*ContourAnalysisTest*:*LineDetectionTest*:*HoughCircleTest*:*MinEnclosingCircleTest*:*PolygonTest*:*ConvexHullTest*"

.PHONY: CH7_binary_analysis.BinaryMethodCompareTest
CH7_binary_analysis.BinaryMethodCompareTest: build-debug-check
	@echo "Running BinaryMethodCompareTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*BinaryMethodCompareTest*"

.PHONY: CH7_binary_analysis.ConnectedComponentLabelingTest
CH7_binary_analysis.ConnectedComponentLabelingTest: build-debug-check
	@echo "Running ConnectedComponentLabelingTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ConnectedComponentLabelingTest*"

.PHONY: CH7_binary_analysis.FindContoursTest
CH7_binary_analysis.FindContoursTest: build-debug-check
	@echo "Running FindContoursTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*FindContoursTest*"

.PHONY: CH7_binary_analysis.DrawContoursTest
CH7_binary_analysis.DrawContoursTest: build-debug-check
	@echo "Running DrawContoursTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*DrawContoursTest*"

.PHONY: CH7_binary_analysis.ContourMeatureTest
CH7_binary_analysis.ContourMeatureTest: build-debug-check
	@echo "Running ContourMeatureTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ContourMeatureTest*"

.PHONY: CH7_binary_analysis.MomentsTest
CH7_binary_analysis.MomentsTest: build-debug-check
	@echo "Running MomentsTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*MomentsTest*"

.PHONY: CH7_binary_analysis.FitAndApproxTest
CH7_binary_analysis.FitAndApproxTest: build-debug-check
	@echo "Running FitAndApproxTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*FitAndApproxTest*"

.PHONY: CH7_binary_analysis.EllipseFitTest
CH7_binary_analysis.EllipseFitTest: build-debug-check
	@echo "Running EllipseFitTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*EllipseFitTest*"

.PHONY: CH7_binary_analysis.LineFitTest
CH7_binary_analysis.LineFitTest: build-debug-check
	@echo "Running LineFitTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*LineFitTest*"

.PHONY: CH7_binary_analysis.ApproxPolyDPTest
CH7_binary_analysis.ApproxPolyDPTest: build-debug-check
	@echo "Running ApproxPolyDPTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ApproxPolyDPTest*"

.PHONY: CH7_binary_analysis.ContourAnalysisTest
CH7_binary_analysis.ContourAnalysisTest: build-debug-check
	@echo "Running ContourAnalysisTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ContourAnalysisTest*"

.PHONY: CH7_binary_analysis.LineDetectionTest
CH7_binary_analysis.LineDetectionTest: build-debug-check
	@echo "Running LineDetectionTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*LineDetectionTest*"

.PHONY: CH7_binary_analysis.HoughCircleTest
CH7_binary_analysis.HoughCircleTest: build-debug-check
	@echo "Running HoughCircleTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*HoughCircleTest*"

.PHONY: CH7_binary_analysis.MinEnclosingCircleTest
CH7_binary_analysis.MinEnclosingCircleTest: build-debug-check
	@echo "Running MinEnclosingCircleTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*MinEnclosingCircleTest*"

.PHONY: CH7_binary_analysis.PolygonTest
CH7_binary_analysis.PolygonTest: build-debug-check
	@echo "Running PolygonTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*PolygonTest*"

.PHONY: CH7_binary_analysis.ConvexHullTest
CH7_binary_analysis.ConvexHullTest: build-debug-check
	@echo "Running ConvexHullTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*ConvexHullTest*"


# ============================================
# CH8_morphology 测试规则
# ============================================

.PHONY: CH8_morphology
CH8_morphology: build-debug-check
	@echo "========================================"
	@echo "Running all tests in CH8_morphology.cc"
	@echo "========================================"
	@$(TEST_EXEC_DEBUG) --gtest_filter="*MorphologyTest*:*DilateErodeTest*:*OpenCloseTest*:*MorphGradientTest*:*EdgeDetectTest*:*HatTest*:*HitTest*"

.PHONY: CH8_morphology.MorphologyTest
CH8_morphology.MorphologyTest: build-debug-check
	@echo "Running MorphologyTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*MorphologyTest*"

.PHONY: CH8_morphology.DilateErodeTest
CH8_morphology.DilateErodeTest: build-debug-check
	@echo "Running DilateErodeTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*DilateErodeTest*"

.PHONY: CH8_morphology.OpenCloseTest
CH8_morphology.OpenCloseTest: build-debug-check
	@echo "Running OpenCloseTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*OpenCloseTest*"

.PHONY: CH8_morphology.MorphGradientTest
CH8_morphology.MorphGradientTest: build-debug-check
	@echo "Running MorphGradientTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*MorphGradientTest*"

.PHONY: CH8_morphology.EdgeDetectTest
CH8_morphology.EdgeDetectTest: build-debug-check
	@echo "Running EdgeDetectTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*EdgeDetectTest*"

.PHONY: CH8_morphology.HatTest
CH8_morphology.HatTest: build-debug-check
	@echo "Running HatTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*HatTest*"

.PHONY: CH8_morphology.HitTest
CH8_morphology.HitTest: build-debug-check
	@echo "Running HitTest..."
	@$(TEST_EXEC_DEBUG) --gtest_filter="*HitTest*"


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

