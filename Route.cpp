#include "Route.h"
#include <string>

Route::Route(std::string airlineCode, int airlineId, std::string sourceCode, int sourceId,
                std::string destinationCode, int destinationId, int stops) {
    airlineCode_ = airlineCode;
    airlineId_ = airlineId;
    sourceCode_ = sourceCode;
    sourceId_ = sourceId;
    destinationCode_ = destinationCode;
    destinationId_ = destinationId;
    stops_ = stops;
}