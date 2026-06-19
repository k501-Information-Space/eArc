Here are the ready-to-use `pyproject.toml` and `Makefile` for the K501-Aionarc repository, designed for a modern Python monorepo with `uv` as the dependency manager, `ruff` for linting, and `pytest` for testing.[[dev](https://dev.to/thomas_bury_b1a50c1156cbf/mastering-python-project-management-with-uv-part-2-deep-dives-and-advanced-use-4mlb)]

---

## `pyproject.toml`

text

`[build-system] requires = ["hatchling>=1.21.0"] build-backend = "hatchling.build" [project] name = "k501-aionarc" version = "0.1.0" description = "Local-first provenance operating system for auditable knowledge continuity" readme = "README.md" license = { text = "MIT" } requires-python = ">=3.11" authors = [     { name = "Patrick Miller", email = "patrice@example.com" } ] keywords = [     "rag",    "provenance",    "memory-system",    "local-first",    "auditability",    "knowledge-persistence",    "agent-memory",    "cognitive-architecture" ] classifiers = [     "Development Status :: 3 - Alpha",    "Intended Audience :: Developers",    "License :: OSI Approved :: MIT License",    "Programming Language :: Python :: 3",    "Programming Language :: Python :: 3.11",    "Programming Language :: Python :: 3.12",    "Topic :: Scientific/Engineering :: Artificial Intelligence", ] dependencies = [     # Core    "python>=3.11",    "msgspec>=0.18.0",    "pydantic>=2.5.0",    "pydantic-settings>=2.1.0",     # HTTP / API    "fastapi>=0.115.0",    "uvicorn>=0.30.0",    "httpx>=0.27.0",     # Persistence    "aiosqlite>=0.19.0",    "sqlalchemy>=2.0.0",     # Vector / Embeddings    "numpy>=1.24.0",    "scikit-learn>=1.3.0",     # Graph    "networkx>=3.1.0",     # Logging / Observability    "structlog>=24.1.0",    "python-json-logger>=2.0.0",     # Utils    "orjson>=3.9.0",    "tenacity>=8.2.0",    "click>=8.1.0", ] [project.optional-dependencies] dev = [     # Testing    "pytest>=7.4.0",    "pytest-asyncio>=0.21.0",    "pytest-cov>=4.1.0",     # Linting / Formatting    "ruff>=0.3.0",    "mypy>=1.8.0",     # Type stubs    "types-orjson>=6.0.0",    "types-click>=8.0.0",     # Docs    "mkdocs>=1.5.0",    "mkdocstrings>=0.24.0",    "mkdocs-material>=9.4.0",     # Misc    "pre-commit>=3.5.0", ] [tool.hatch.build.targets.wheel] packages = ["src/k501"] [tool.ruff] line-length = 100 target-version = "py311" [tool.ruff.lint] select = [     "E",   # pycodestyle errors    "W",   # pycodestyle warnings    "F",   # flake8    "I",   # isort    "B",   # flake8-bugbear    "C4",  # flake8-comprehensions    "UP",  # pyupgrade ] ignore = [     "E501",  # line too long (handled by formatter) ] [tool.mypy] python_version = "3.11" strict = true explicit_package_bases = true ignore_missing_imports = true [tool.pytest.ini_options] asyncio_mode = "auto" testpaths = ["tests"] python_files = ["test_*.py"] addopts = [     "-v",    "--cov=src/k501",    "--cov-report=term-missing",    "--cov-report=html:htmlcov", ] [tool.uv] dev-dependencies = [     "pytest>=7.4.0",    "pytest-asyncio>=0.21.0",    "pytest-cov>=4.1.0",    "ruff>=0.3.0",    "mypy>=1.8.0", ]`

---

## `Makefile`

makefile

`# K501-Aionarc Makefile # Uses uv for dependency management .DEFAULT_GOAL := help # --- Variables --- PROJECT_NAME := k501-aionarc PYTHON_VERSION := 3.11 VENV_DIR := .venv # --- Helpers --- .PHONY: help help: ## Show this help 	@echo "K501-Aionarc Makefile" 	@echo "" 	@echo "Usage:" 	@echo "  make <command>" 	@echo "" 	@echo "Commands:" 	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  %-12s %s\n", $$1, $$2}' .PHONY: sync sync: ## Install/upgrade dependencies with uv 	uv sync .PHONY: lock lock: ## Update lock file 	uv lock .PHONY: upgrade upgrade: ## Upgrade all dependencies 	uv lock --upgrade .PHONY: install install: sync ## Alias for sync # --- Environment --- .PHONY: venv venv: ## Create virtual environment (handled by uv) 	uv sync .PHONY: clean-venv clean-venv: ## Remove virtual environment 	rm -rf $(VENV_DIR) .python-version # --- Linting --- .PHONY: lint lint: ## Run ruff linting 	uv run ruff check src tests .PHONY: format format: ## Run ruff formatting 	uv run ruff format src tests .PHONY: lint-fix lint-fix: ## Run ruff linting with fixes 	uv run ruff check --fix src tests .PHONY: format-fix format-fix: ## Run ruff formatting with fixes 	uv run ruff format src tests .PHONY: typecheck typecheck: ## Run mypy type checking 	uv run mypy src/k501 .PHONY: check check: lint typecheck ## Run all static checks # --- Testing --- .PHONY: test test: ## Run pytest tests 	uv run pytest .PHONY: test-cov test-cov: ## Run pytest with coverage 	uv run pytest --cov=src/k501 --cov-report=term-missing --cov-report=html:htmlcov .PHONY: test-unit test-unit: ## Run unit tests only 	uv run pytest tests/unit .PHONY: test-integration test-integration: ## Run integration tests only 	uv run pytest tests/integration .PHONY: test-e2e test-e2e: ## Run end-to-end tests only 	uv run pytest tests/e2e # --- Documentation --- .PHONY: docs docs: ## Build documentation with mkdocs 	uv run mkdocs build --clean --strict .PHONY: docs-serve docs-serve: ## Serve documentation locally 	uv run mkdocs serve # --- Development --- .PHONY: pre-commit pre-commit: ## Install pre-commit hooks 	uv run pre-commit install .PHONY: pre-commit-run pre-commit-run: ## Run pre-commit on all files 	uv run pre-commit run --all-files # --- Build & Distribution --- .PHONY: build build: ## Build the package 	uv build .PHONY: dist dist: build ## Alias for build .PHONY: clean-build clean-build: ## Remove build artifacts 	rm -rf build dist .egg src/*.egg-info # --- Docker --- .PHONY: docker-build docker-build: ## Build Docker image 	docker build -t $(PROJECT_NAME):latest . .PHONY: docker-run docker-run: ## Run Docker container 	docker run --rm -it $(PROJECT_NAME):latest .PHONY: docker-compose-up docker-compose-up: ## Start docker-compose services 	docker-compose up .PHONY: docker-compose-down docker-compose-down: ## Stop docker-compose services 	docker-compose down # --- Cleanup --- .PHONY: clean clean: clean-build clean-venv ## Remove all build artifacts and venv 	rm -rf htmlcov .pytest_cache .mypy_cache __pycache__ 	rm -rf .ruff_cache .coverage .PHONY: all all: check test build ## Run all checks, tests, and build # --- Developer shortcuts --- .PHONY: dev-setup dev-setup: sync pre-commit docs-serve ## Full developer setup .PHONY: quick-check quick-check: lint test ## Quick lint + test`

---

## Usage Notes

1. **Install dependencies**:
    
    bash
    
    `make sync`
    
2. **Run tests**:
    
    bash
    
    `make test`
    
3. **Run linting**:
    
    bash
    
    `make lint make format make typecheck`
    
4. **Build docs**:
    
    bash
    
    `make docs make docs-serve`
    
5. **Full build**:
    
    bash
    
    `make all`
    

These files are ready to drop into the repository root alongside `README.md`, `LICENSE`, `.gitignore`, and `uv.lock`.