//ACTIONS
export const requestMusic = "requestMusic";
export const actions = {
  requestMusic,
};

//MUTATIONS
export const addSong = "addSong";
export const mutations = {
  addSong,
};

//GETTERS
export const getters = {};

const audio_types = {
  ...actions,
  ...mutations,
  ...getters,
};

export default audio_types;
