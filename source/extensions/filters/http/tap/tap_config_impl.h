#pragma once

#include "envoy/http/header_map.h"

#include "extensions/filters/http/tap/tap_config.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace TapFilter {

class TapConfigBaseImpl {
protected:
  TapConfigBaseImpl(envoy::service::tap::v2alpha::TapConfig&&) {}
};

class HttpTapConfigImpl : TapConfigBaseImpl,
                          public HttpTapConfig,
                          public std::enable_shared_from_this<HttpTapConfigImpl> {
public:
  HttpTapConfigImpl(envoy::service::tap::v2alpha::TapConfig&& proto_config,
                    HttpTapSink& admin_streamer)
      : TapConfigBaseImpl(std::move(proto_config)), admin_streamer_(admin_streamer) {
    // fixfix assert admin streamer output type.
  }

  bool matchesRequestHeaders(const Http::HeaderMap& headers);
  bool matchesResponseHeaders(const Http::HeaderMap& headers);
  HttpTapSink& sink() { return admin_streamer_; }

  // TapFilter::HttpTapConfig
  HttpPerRequestTapperPtr newPerRequestTapper() override;

private:
  HttpTapSink& admin_streamer_;
};

typedef std::shared_ptr<HttpTapConfigImpl> HttpTapConfigImplSharedPtr;

class HttpPerRequestTapperImpl : public HttpPerRequestTapper {
public:
  HttpPerRequestTapperImpl(HttpTapConfigImplSharedPtr config) : config_(config) {}

  // TapFilter::HttpPerRequestTapper
  void onRequestHeaders(const Http::HeaderMap& headers) override;
  void onResponseHeaders(const Http::HeaderMap& headers) override;

private:
  HttpTapConfigImplSharedPtr config_;
  // bool tapping_{};
};

} // namespace TapFilter
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
