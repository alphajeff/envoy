#include "extensions/filters/http/tap/tap_config_impl.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace TapFilter {

bool HttpTapConfigImpl::matchesRequestHeaders(const Http::HeaderMap&) { return true; }

bool HttpTapConfigImpl::matchesResponseHeaders(const Http::HeaderMap&) { return true; }

HttpPerRequestTapperPtr HttpTapConfigImpl::newPerRequestTapper() {
  return std::make_unique<HttpPerRequestTapperImpl>(shared_from_this());
}

void HttpPerRequestTapperImpl::onRequestHeaders(const Http::HeaderMap&) {}

void HttpPerRequestTapperImpl::onResponseHeaders(const Http::HeaderMap&) {}

} // namespace TapFilter
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
