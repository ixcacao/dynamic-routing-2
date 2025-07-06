enum MeshMessageType {
  RH_MESH_MESSAGE_TYPE_APPLICATION = 1,
  RH_MESH_MESSAGE_TYPE_ROUTE_DISCOVERY_REQUEST = 2,
  RH_MESH_MESSAGE_TYPE_ROUTE_DISCOVERY_RESPONSE = 3,
  RH_MESH_MESSAGE_TYPE_ROUTE_FAILURE = 4
};

struct MeshMessageHeader {
  uint8_t messageType;
  uint8_t source;
  uint8_t destination;
};

struct MeshApplicationMessage {
  MeshMessageHeader header;
  uint8_t payload[32];
};

struct MeshRouteDiscoveryMessage {
  MeshMessageHeader header;
  uint8_t route[10]; // list of node IDs visited
  uint8_t routeLength;
};

struct MeshRouteFailureMessage {
  MeshMessageHeader header;
  uint8_t failedNode;
};
