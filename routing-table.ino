#define MAX_ROUTES 10

struct RouteEntry {
  uint8_t destination;
  uint8_t nextHop;
  uint8_t hops;
};

RouteEntry routingTable[MAX_ROUTES];
