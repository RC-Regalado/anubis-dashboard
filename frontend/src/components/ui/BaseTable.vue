<template>
  <div class="base-table">
    <table>
      <thead>
        <tr>
          <th v-for="column in columns" :key="column.key">{{ column.label }}</th>
        </tr>
      </thead>
      <tbody>
        <tr v-if="!rows.length">
          <td :colspan="columns.length" class="base-table__empty">Sin registros</td>
        </tr>
        <tr v-for="row in rows" :key="row.id">
          <td v-for="column in columns" :key="column.key">
            <slot :name="column.key" :row="row">
              {{ row[column.key] }}
            </slot>
          </td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script setup lang="ts">
interface TableColumn {
  key: string
  label: string
}

defineProps<{
  columns: TableColumn[]
  rows: Array<Record<string, unknown> & { id: string }>
}>()
</script>

<style scoped lang="scss">
.base-table {
  overflow-x: auto;
  border: 1px solid #d8dee8;
  border-radius: 8px;
  background: #ffffff;
}

table {
  width: 100%;
  border-collapse: collapse;
}

th,
td {
  padding: 0.85rem 1rem;
  border-bottom: 1px solid #e7ebf1;
  text-align: left;
  vertical-align: middle;
}

th {
  color: #607089;
  font-size: 0.78rem;
  text-transform: uppercase;
}

tr:last-child td {
  border-bottom: 0;
}

.base-table__empty {
  color: #607089;
  text-align: center;
}
</style>
