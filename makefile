# 定义伪目标
.PHONY: clean dry-run

# --- 配置部分 ---
# 当前目录 (根目录)
ROOT_DIR = .
# LeetCode 所在的具体路径 (根据截图修改)
LEETCODE_DIR = code/leetcode

# --- 规则部分 ---

clean:
	@echo "========================================"
	@echo "Cleaning workspace..."
	@echo "========================================"

	@# [1] Rust 项目清理
	@# 逻辑：从根目录开始找 Cargo.toml，进入所在目录执行 cargo clean
	@echo "[Rust Projects]"
	@find $(ROOT_DIR) -name "Cargo.toml" -type f | while read toml_file; do \
		target_dir=$$(dirname "$$toml_file"); \
		echo "-> Running 'cargo clean' in: $$target_dir"; \
		(cd "$$target_dir" && cargo clean); \
	done

	@# [2] C++ 项目清理 (重点修改了这里的路径)
	@# 逻辑：检查 code/leetcode 是否存在，然后删除下面所有的 output 文件夹
	@echo ""
	@echo "[C++ Output Directories]"
	@if [ -d "$(LEETCODE_DIR)" ]; then \
		find $(LEETCODE_DIR) -type d -name "output" -exec rm -rf {} + 2>/dev/null; \
		echo "-> Cleaned: 'output' directories in $(LEETCODE_DIR)"; \
	else \
		echo "-> Skipped: Directory '$(LEETCODE_DIR)' not found"; \
	fi

	@# [3] 清理所有的 .exe 文件
	@# 逻辑：从根目录开始递归删除所有 .exe
	@echo ""
	@echo "[Executable Files]"
	@find $(ROOT_DIR) -type f -name "*.exe" -exec rm -f {} + 2>/dev/null
	@echo "-> Cleaned: All .exe files"
	
	@echo "========================================"
	@echo "Done! All artifacts cleaned."

# --- 预览模式 (Dry Run) ---
# 只看不删，用于测试
dry-run:
	@echo "=== Preview: What will be cleaned? ==="
	@echo "[Rust Projects]"
	@find $(ROOT_DIR) -name "Cargo.toml" -type f | while read file; do \
		echo "  Found: $$(dirname "$$file")"; \
	done
	@echo ""
	@echo "[Directories to be removed]"
	@if [ -d "$(LEETCODE_DIR)" ]; then \
		find $(LEETCODE_DIR) -type d -name "output"; \
	else \
		echo "  ! Directory '$(LEETCODE_DIR)' not found"; \
	fi
	@echo ""
	@echo "[Files to be removed]"
	@find $(ROOT_DIR) -type f -name "*.exe"