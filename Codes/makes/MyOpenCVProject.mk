# ============================================
# 可执行文件配置：MyOpenCVProject（带运行检测）
# ============================================

EXECUTABLE := MyOpenCVProject

# 定义运行命令（供主 Makefile 使用）
define RUN_CMD_DEBUG
	@if [ -f "./build-debug/bin/$(EXECUTABLE)" ]; then \
		./build-debug/bin/$(EXECUTABLE); \
	else \
		echo "Error: $(EXECUTABLE) not found in build-debug"; \
		exit 1; \
	fi
endef

define RUN_CMD_RELEASE
	@if [ -f "./build-release/bin/$(EXECUTABLE)" ]; then \
		./build-release/bin/$(EXECUTABLE); \
	else \
		echo "Error: $(EXECUTABLE) not found in build-release"; \
		exit 1; \
	fi
endef

# 可选：智能运行（自动选择 Debug 或 Release）
define RUN_CMD_SMART
	@if [ -f "./build-debug/bin/$(EXECUTABLE)" ]; then \
		./build-debug/bin/$(EXECUTABLE); \
	elif [ -f "./build-release/bin/$(EXECUTABLE)" ]; then \
		./build-release/bin/$(EXECUTABLE); \
	else \
		echo "Error: $(EXECUTABLE) not found in build-debug or build-release"; \
		exit 1; \
	fi
endef
