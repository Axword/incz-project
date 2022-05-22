import Measurement from "../service/measurement";

const state = {
  totalMeasurementsItems: 0,
  measurementList: [],
  measurementDetails: {},
  errors: {},
  measurementListHeaders: [
    {
      text: "timestamp",
      value: "timestamp",
    },
    {
      text: "Pomiar X",
      value: "measure_y_one",
    },
    {
      text: "Pomiar Y",
      value: "measure_y_two",
    },
    {
      text: "Pomiar Z",
      value: "measure_z_one",
      sortable: false,
    },
  ],
  measurementsPerPage: 5,
};

const mutations = {
  setMeasurementList(state, payload) {
    state.totalMeasurementsItems = payload.count;
    state.measurementList = [...payload];
  },
  setMeasurementsItemsPerPage(state, payload) {
    state.measurementsPerPage = payload;
  },
};
const actions = {
  async fetchMeasurementList(context, params) {
    context.commit("setMeasurementList", await Measurement.list(params));
  },

  async deleteMeasurement({ commit }, payload) {
    await new Measurement(payload).remove();
    commit("showMessage", "Koszyk został pomyślnie usunięty.");
  },
};

export default {
  state,
  mutations,
  actions,
};
