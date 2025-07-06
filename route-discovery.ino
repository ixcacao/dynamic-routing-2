void startRouteDiscovery(uint8_t dest) {
  MeshRouteDiscoveryMessage req;
  req.header.messageType = RH_MESH_MESSAGE_TYPE_ROUTE_DISCOVERY_REQUEST;
  req.header.source = getNodeId();
  req.header.destination = dest;
  req.routeLength = 1;
  req.route[0] = getNodeId();
  broadcast((uint8_t*)&req, sizeof(req));
}

void onReceiveRouteDiscovery(MeshRouteDiscoveryMessage* msg) {
  // Avoid loops
  if (isInRoute(msg->route, msg->routeLength, getNodeId())) return;

  // Append self to route
  msg->route[msg->routeLength++] = getNodeId();

  if (msg->header.destination == getNodeId()) {
    // Send RESPONSE back
    MeshRouteDiscoveryMessage resp;
    resp.header.messageType = RH_MESH_MESSAGE_TYPE_ROUTE_DISCOVERY_RESPONSE;
    resp.header.source = getNodeId();
    resp.header.destination = msg->header.source;
    memcpy(resp.route, msg->route, msg->routeLength);
    resp.routeLength = msg->routeLength;
    unicast((uint8_t*)&resp, sizeof(resp), msg->route[msg->routeLength - 2]); // backtrack
  } else {
    // Re-broadcast request
    broadcast((uint8_t*)msg, sizeof(*msg));
  }

  // Learn route to the source
  if (msg->routeLength > 1)
    addRoute(msg->header.source, msg->route[msg->routeLength - 2], msg->routeLength - 1);
}
