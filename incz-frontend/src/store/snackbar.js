const state = {
  opened: false,
  message: "",
  color: "success",
};

const getters = {
  isSnackbarOpened(state) {
    return state.opened;
  },
  getSnackbarMessage(state) {
    return state.message;
  },
  getSnackbarColor(state) {
    return state.color;
  },
};

const mutations = {
  showMessage(state, { message, color = "success" }) {
    state.opened = true;
    state.message = message;
    state.color = color;
  },
  hideMessage(state) {
    state.opened = false;
    state.message = "";
    state.color = "success";
  },
};

export default {
  state,
  getters,
  mutations,
};
