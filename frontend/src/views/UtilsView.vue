<template>
  <UtilsLayout>
    <template #actions>
      <div class="actions">
        <button class="btn btn-primary" type="button" @click="openModal('day')">Registrar dia</button>
        <button class="btn btn-outline-secondary" type="button" @click="openModal('workout')">
          Entrenamiento
        </button>
        <button class="btn btn-outline-secondary" type="button" @click="openModal('meal')">
          Comida
        </button>
        <button class="btn btn-outline-secondary" type="button" @click="openModal('habit')">
          Habito
        </button>
      </div>
    </template>

    <UtilsSummary />

    <section class="utils-grid utils-grid--primary">
      <PhysiologyPanel />
      <NutritionSleepPanel />
    </section>

    <section class="utils-grid utils-grid--secondary">
      <TrainingPerformance />
      <HabitTracker />
      <SubjectiveState />
      <NeatActivity />
    </section>

    <PomodoroNotifier />

    <RelationshipInsights />

    <BaseModal v-model="modalOpen" :title="modalTitle">
      <DailyLogForm v-if="activeModal === 'day'" @saved="closeModal" />
      <WorkoutForm v-if="activeModal === 'workout'" @saved="closeModal" />
      <MealForm v-if="activeModal === 'meal'" @saved="closeModal" />
      <HabitForm v-if="activeModal === 'habit'" @saved="closeModal" />
    </BaseModal>
  </UtilsLayout>
</template>

<script setup lang="ts">
import { computed, ref } from 'vue'
import BaseModal from '@/components/ui/BaseModal.vue'
import UtilsLayout from '@/components/utils/UtilsLayout.vue'
import UtilsSummary from '@/components/utils/UtilsSummary.vue'
import PhysiologyPanel from '@/components/utils/PhysiologyPanel.vue'
import NutritionSleepPanel from '@/components/utils/NutritionSleepPanel.vue'
import TrainingPerformance from '@/components/utils/TrainingPerformance.vue'
import HabitTracker from '@/components/utils/HabitTracker.vue'
import SubjectiveState from '@/components/utils/SubjectiveState.vue'
import NeatActivity from '@/components/utils/NeatActivity.vue'
import RelationshipInsights from '@/components/utils/RelationshipInsights.vue'
import PomodoroNotifier from '@/components/utils/PomodoroNotifier.vue'
import DailyLogForm from '@/components/utils/forms/DailyLogForm.vue'
import WorkoutForm from '@/components/utils/forms/WorkoutForm.vue'
import MealForm from '@/components/utils/forms/MealForm.vue'
import HabitForm from '@/components/utils/forms/HabitForm.vue'

type ModalType = 'day' | 'workout' | 'meal' | 'habit'

const activeModal = ref<ModalType>('day')
const modalOpen = ref(false)

const modalTitle = computed(() => {
  const labels: Record<ModalType, string> = {
    day: 'Registro diario',
    workout: 'Registro de entrenamiento',
    meal: 'Registro de comida',
    habit: 'Nuevo habito',
  }

  return labels[activeModal.value]
})

function openModal(type: ModalType) {
  activeModal.value = type
  modalOpen.value = true
}

function closeModal() {
  modalOpen.value = false
}
</script>

<style scoped lang="scss">
.actions {
  display: flex;
  flex-wrap: wrap;
  justify-content: flex-end;
  gap: 0.5rem;
}

.utils-grid {
  display: grid;
  gap: 1rem;
}

.utils-grid--primary {
  grid-template-columns: repeat(2, minmax(0, 1fr));
}

.utils-grid--secondary {
  grid-template-columns: repeat(4, minmax(0, 1fr));
}

@media (max-width: 1280px) {
  .utils-grid--secondary {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }
}

@media (max-width: 900px) {
  .actions {
    justify-content: flex-start;
  }

  .utils-grid--primary,
  .utils-grid--secondary {
    grid-template-columns: 1fr;
  }
}
</style>
