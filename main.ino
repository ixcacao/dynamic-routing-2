void loop() {
  if (radio.available()) {
    uint8_t buf[64];
    size_t len = sizeof(buf);
    radio.recv(buf, &len);

    MeshMessageHeader* hdr = (MeshMessageHeader*)buf;
    switch (hdr->messageType) {
      case RH_MESH_MESSAGE_TYPE_APPLICATION:
        handleAppMessage((MeshApplicationMessage*)buf); break;
      case RH_MESH_MESSAGE_TYPE_ROUTE_DISCOVERY_REQUEST:
        onReceiveRouteDiscovery((MeshRouteDiscoveryMessage*)buf); break;
      case RH_MESH_MESSAGE_TYPE_ROUTE_DISCOVERY_RESPONSE:
        onReceiveRouteDiscoveryResponse((MeshRouteDiscoveryMessage*)buf); break;
      case RH_MESH_MESSAGE_TYPE_ROUTE_FAILURE:
        onReceiveRouteFailure((MeshRouteFailureMessage*)buf); break;
    }
  }
}
