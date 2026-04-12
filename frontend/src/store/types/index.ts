const types = {
  data: "data",
  request: "request",
  addFile: "addFile",
  setDownloadTarget: "setDownloadTarget",
  getTarget: "getTarget",
  requestMusic: "requestMusic",
  addSong: "addSong",
  readCurses: "readCurses",
  loadCurse: "loadCurse",
  addCurse: "addCurse",
  addVideo: "addVideo",
  setVideo: "setVideo",
  getCurseById: "getCurseById",
  getCurseIndexById: "getCurseIndexById",
  getVideoById: "getVideoById",
  resetFiles: "resetFiles",
  resetCurses: "resetCurses",
  resetSongs: "resetSongs",
} as const;

export default types;
