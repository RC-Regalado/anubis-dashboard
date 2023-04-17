export const readCurses = "readCurses";
export const loadCurse = "loadCurse";
const actions = {
  readCurses,
  loadCurse,
};

export const addCurse = "addCurse";
export const addVideo = "addVideo";
export const setVideo = "setVideo";
const mutations = {
  addCurse,
  addVideo,
  setVideo,
};

export const getCurseById = "getCurseById";
export const getCurseIndexById = "getCurseIndexById";
export const getVideoById = "getVideoById";
const getters = {
  getCurseById,
  getCurseIndexById,
  getVideoById,
};

const video_types = {
  ...actions,
  ...mutations,
  ...getters,
};

export default video_types;
