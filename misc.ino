bool isInRoute(uint8_t* route, uint8_t len, uint8_t id) {
  for (int i = 0; i < len; ++i)
    if (route[i] == id) return true;
  return false;
}