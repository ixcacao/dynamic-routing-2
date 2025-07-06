void onNextHopUnreachable(uint8_t dest) {
  MeshRouteFailureMessage failure;
  failure.header.messageType = RH_MESH_MESSAGE_TYPE_ROUTE_FAILURE;
  failure.header.source = getNodeId();
  failure.header.destination = getOriginalSender(dest);
  failure.failedNode = dest;
  unicast((uint8_t*)&failure, sizeof(failure), getNextHop(failure.header.destination));
}

void onReceiveRouteFailure(MeshRouteFailureMessage* msg) {
  deleteRoute(msg->failedNode);
  if (msg->header.destination != getNodeId()) {
    unicast((uint8_t*)msg, sizeof(*msg), getNextHop(msg->header.destination));
  }
}
