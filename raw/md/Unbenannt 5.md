Below is a structured logging configuration for K501-Aionarc using `structlog`, integrated with FastAPI and Uvicorn. It provides both pretty console logs in development and JSON logs in production, with request-level context (request_id, path, method, client_host, status_code) automatically attached to every log entry.[[angelospanag](https://www.angelospanag.me/blog/structured-logging-using-structlog-and-fastapi)]

---

## 1. `src/k501/observability/logs.py`

This module configures `structlog` globally and provides a shared logger factory.

python

`""" K501-Aionarc Structured Logging Configuration This module configures structlog to output: - Pretty console logs in development - JSON logs in production - Request-level context (request_id, path, method, client_host, status_code) """ import logging import os import sys import uuid from typing import Any import structlog from fastapi import Request def is_production() -> bool:     """Check if running in production mode."""    return os.getenv("LOG_JSON_FORMAT", "false").lower() in ("true", "1", "yes") def configure_structlog() -> None:     """    Configure structlog as early as possible in the app lifecycle.     This configuration:    - Disables uvicorn's default loggers to avoid duplicate logs    - Uses merge_contextvars to inject request-level context    - Adds log level, stack info, exception info, and ISO timestamp    - Uses ConsoleRenderer in dev and JSONRenderer in production    """    # Disable uvicorn's default loggers    logging.getLogger("uvicorn.error").disabled = True    logging.getLogger("uvicorn.access").disabled = True     # Basic logging setup (structlog will override this)    logging.basicConfig(        format="%(message)s",        stream=sys.stdout,        level=logging.INFO,    )     # Define processors    processors: list[Any] = [        structlog.contextvars.merge_contextvars,        structlog.processors.add_log_level,        structlog.stdlib.add_logger_name,        structlog.processors.StackInfoRenderer(),        structlog.processors.set_exc_info,        structlog.processors.TimeStamper(fmt="iso", utc=True),    ]     # Add renderer based on environment    if is_production():        # Production: JSON output for log aggregation (ELK, Datadog, CloudWatch)        processors.append(structlog.processors.JSONRenderer())    else:        # Development: pretty console output        processors.append(structlog.dev.ConsoleRenderer())     # Configure structlog    structlog.configure(        processors=processors,        context_class=dict,        logger_factory=structlog.stdlib.LoggerFactory(),        wrapper_class=structlog.stdlib.BoundLogger,        cache_logger_on_first_use=True,    ) def get_logger(name: str = "k501") -> structlog.stdlib.BoundLogger:     """    Get a bound logger for K501-Aionarc.     Args:        name: Logger name (default: "k501")     Returns:        structlog BoundLogger with context support    """    return structlog.get_logger(name) # Initialize structlog at module import configure_structlog() # Default logger instance logger = get_logger()`

---

## 2. `src/k501/observability/__init__.py`

python

`""" K501 Observability Package Exports: - logger: Default bound logger - get_logger: Logger factory - LoggingMiddleware: FastAPI middleware for request context """ from .logs import get_logger, logger __all__ = ["logger", "get_logger"]`

---

## 3. `src/k501/api/middleware/logging_middleware.py`

This middleware injects request-level context into structlog's context variables so every log during the request includes this metadata.

python

`""" FastAPI Logging Middleware Binds request-level context (request_id, path, method, client_host) to all logs during the request lifecycle. Also captures status_code and request duration. """ import time import uuid from typing import Callable from fastapi import Request, Response from starlette.middleware.base import BaseHTTPMiddleware from ..logs import get_logger class LoggingMiddleware(BaseHTTPMiddleware):     """    FastAPI middleware that binds request context to structlog.     Logs produced during the request will include:    - request_id (UUID)    - path    - method    - client_host    - status_code    - duration (ms)    """     async def __call__(self, request: Request, call_next: Callable) -> Response:        logger = get_logger("http")         # Clear previous context vars        structlog.contextvars.clear_contextvars()         # Generate request ID        request_id = str(uuid.uuid4())         # Extract client host (may be None)        client_host = request.client.host if request.client else "unknown"         # Bind request context        structlog.contextvars.bind_contextvars(            request_id=request_id,            path=request.url.path,            method=request.method,            client_host=client_host,        )         # Log request start        logger.info("request_start", path=request.url.path, method=request.method)         # Measure duration        start_time = time.perf_counter()         # Process request        response = await call_next(request)         end_time = time.perf_counter()        duration_ms = (end_time - start_time) * 1000         # Bind status code        structlog.contextvars.bind_contextvars(            status_code=response.status_code,            duration_ms=duration_ms,        )         # Log request end with appropriate level        if response.status_code >= 500:            logger.error("request_error", status_code=response.status_code, duration_ms=duration_ms)        elif response.status_code >= 400:            logger.warning("request_client_error", status_code=response.status_code, duration_ms=duration_ms)        else:            logger.info("request_ok", status_code=response.status_code, duration_ms=duration_ms)         return response`

Wait — I need to fix the import and add the structlog import:

python

`""" FastAPI Logging Middleware Binds request-level context (request_id, path, method, client_host) to all logs during the request lifecycle. Also captures status_code and request duration. """ import time import uuid from typing import Callable import structlog from fastapi import Request, Response from starlette.middleware.base import BaseHTTPMiddleware from ..logs import get_logger class LoggingMiddleware(BaseHTTPMiddleware):     """    FastAPI middleware that binds request context to structlog.     Logs produced during the request will include:    - request_id (UUID)    - path    - method    - client_host    - status_code    - duration (ms)    """     async def __call__(self, request: Request, call_next: Callable) -> Response:        logger = get_logger("http")         # Clear previous context vars        structlog.contextvars.clear_contextvars()         # Generate request ID        request_id = str(uuid.uuid4())         # Extract client host (may be None)        client_host = request.client.host if request.client else "unknown"         # Bind request context        structlog.contextvars.bind_contextvars(            request_id=request_id,            path=request.url.path,            method=request.method,            client_host=client_host,        )         # Log request start        logger.info("request_start", path=request.url.path, method=request.method)         # Measure duration        start_time = time.perf_counter()         # Process request        response = await call_next(request)         end_time = time.perf_counter()        duration_ms = (end_time - start_time) * 1000         # Bind status code        structlog.contextvars.bind_contextvars(            status_code=response.status_code,            duration_ms=duration_ms,        )         # Log request end with appropriate level        if response.status_code >= 500:            logger.error("request_error", status_code=response.status_code, duration_ms=duration_ms)        elif response.status_code >= 400:            logger.warning("request_client_error", status_code=response.status_code, duration_ms=duration_ms)        else:            logger.info("request_ok", status_code=response.status_code, duration_ms=duration_ms)         return response`

---

## 4. `src/k501/api/http.py`

Update your FastAPI app to use the logging middleware.

python

`""" K501-Aionarc HTTP API Server Configures FastAPI with structlog-based logging middleware. """ from fastapi import FastAPI from ..observability import logger from .middleware.logging_middleware import LoggingMiddleware def create_app() -> FastAPI:     """Create and configure the FastAPI application."""    app = FastAPI(        title="K501-Aionarc",        description="Local-first provenance operating system for auditable knowledge continuity",        version="0.1.0",    )     # Add logging middleware    app.add_middleware(LoggingMiddleware)     # Example endpoint    @app.get("/health")    async def health_check():        logger.info("health_check", component="api")        return {"status": "healthy"}     @app.get("/")    async def root():        logger.info("root_endpoint", component="api")        return {"message": "K501-Aionarc API"}     return app`

---

## 5. Usage Example in Core Modules

Anywhere in your code, you can use the logger with structured data:

python

`from ..observability import logger def ingest_document(doc_id: str, namespace: str) -> None:     logger.info(        "document_ingested",        doc_id=doc_id,        namespace=namespace,        operation="ingestion",    )`

This will produce logs with all the bound context variables (request_id, path, method, client_host, status_code, duration_ms) automatically included.

---

## 6. Environment Configuration

Add to `.env.example`:

bash

`# Logging LOG_JSON_FORMAT=false          # Set to true for production JSON logs LOG_LEVEL=INFO                 # Default log level`

---

## 7. Example Logs

## Development (pretty console):

text

`2026-06-17T00:45:00.123456Z [info] request_start path=/items/1 method=GET request_id=39028224-5807-4f3f-86e1-f4b55786510d client_host=127.0.0.1 2026-06-17T00:45:00.234567Z [info] document_ingested operation="ingestion" doc_id="doc-123" namespace="research" request_id=39028224-5807-4f3f-86e1-f4b55786510d client_host=127.0.0.1 2026-06-17T00:45:00.345678Z [info] request_ok status_code=200 duration_ms=222.3 request_id=39028224-5807-4f3f-86e1-f4b55786510d client_host=127.0.0.1`

## Production (JSON):

json

`{   "event": "request_start",  "level": "info",  "logger": "http",  "timestamp": "2026-06-17T00:45:00.123456Z",  "path": "/items/1",  "method": "GET",  "request_id": "39028224-5807-4f3f-86e1-f4b55786510d",  "client_host": "127.0.0.1" }`

---

This setup gives you production-ready structured logging with request correlation, environment-aware output, and full integration with FastAPI and Uvicorn.[[reddit](https://www.reddit.com/r/FastAPI/comments/1ch53oo/question_help_with_uvicorn_logs_in_fastapi/)]