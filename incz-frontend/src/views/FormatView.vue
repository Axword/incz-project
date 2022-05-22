<template>
  <div class="measurement">
    <v-main class="elevation-0 mt-4 px-5 py-3">
      <v-btn class="my-3" outlined large title="Wróć" @click="back">Wróć do listy koszyków</v-btn>
      <TestTable
        :headers="headers"
        :items="items"
        :items-count="count"
        :get-items-per-page="itemsPerPage"
        :set-items-per-page="setMeasurementsItemsPerPage"
        :fetch-objects="fetchMeasurementList"
        :fetch-object-params="{ 'cart_id': cartId }"
        locale="pl-PL"
        class="elevation-1"
      >
      </TestTable>
    </v-main>
  </div>
</template>

<script>
// @ is an alias to /src
import TestTable from "@/components/TestTable";
import { mapState, mapMutations, mapActions } from "vuex";
import router from "@/router";
export default {
  name: "MeasurementTable",
  components: { TestTable },
  data() {
    return {
      options: {
        sortBy: ['id'],
        offset: 5,
        page: 0
      },
    };
  },
  methods: {
    ...mapMutations(["setMeasurementsItemsPerPage"]),
    ...mapActions(["fetchMeasurementList", "deleteMeasurement"]),
    async deleteItem(item) {
      (await confirm("Czy na pewno chcesz usunąć koszyk?")) &&
        this.deleteMeasurement(item);
    },
    back() {
      router.push({ name: 'CartTable' });
    },
  },
  computed: {
    ...mapState({
      errors: (state) => state.measurement.errors,
      count: (state) => state.measurement.totalMeasurementsItems,
      headers: (state) => state.measurement.measurementListHeaders,
      items: (state) => state.measurement.measurementList,
      itemsPerPage: (state) => state.measurement.measurementsPerPage,
    }),
    cartId() {
      return this.$route.params.id;
  }
  },
  async created() {
    console.log(this.options)
    this.fetchMeasurementList({'cart_id': this.cartId});
  },
};
</script>
xx