//ACTIONS
export const data = "data";
export const request = "request";
export const actions = {
  data,
  request,
};

//MUTATIONS
export const addFile = "addFile";
export const setDownloadTarget = "setDownloadTarget";
export const mutations = {
  addFile,
  setDownloadTarget,
};

//GETTERS
export const getTarget = "getTarget";
export const getters = {
  getTarget,
};

const general_types = {
  ...actions,
  ...mutations,
  ...getters,
};

export default general_types;
