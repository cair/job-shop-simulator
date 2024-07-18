#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/function.h>
#include <nanobind/stl/pair.h>
#include <nanobind/stl/tuple.h>

#include "job_shop_environment.h"
#include "job_shop_qlearning.h"
#include "job_shop_actor_critic.h"
#include "job_shop_taillard_generator.h"
#include "job_shop_plotter.h"

namespace nb = nanobind;

NB_MODULE(jobshop, m) {
    // Bind Job struct
    nb::class_<Job>(m, "Job")
    .def(nb::init<>())
    .def_rw("operations", &Job::operations)
    .def_rw("machines", &Job::machines)
    .def_rw("eligibleMachines", &Job::eligibleMachines);

    // Bind Action struct
    nb::class_<Action>(m, "Action")
    .def(nb::init<>())
    .def(nb::init<int, int, int>())
    .def_rw("job", &Action::job)
    .def_rw("machine", &Action::machine)
    .def_rw("operation", &Action::operation);

    // Bind State struct
    nb::class_<State>(m, "State")
    .def(nb::init<int, int, int>())
    .def_rw("jobProgress", &State::jobProgress)
    .def_rw("machineAvailability", &State::machineAvailability)
    .def_rw("nextOperationForJob", &State::nextOperationForJob);

    // Bind ScheduleEntry struct
    nb::class_<ScheduleEntry>(m, "ScheduleEntry")
    .def(nb::init<>())
    .def(nb::init<int, int, int>())
    .def_rw("job", &ScheduleEntry::job)
    .def_rw("start", &ScheduleEntry::start)
    .def_rw("duration", &ScheduleEntry::duration)
    .def("__getstate__", [](const ScheduleEntry &se) {
        return std::make_tuple(se.job, se.start, se.duration);
    })
    .def("__setstate__", [](ScheduleEntry &se, const std::tuple<int, int, int> &state) {
        new (&se) ScheduleEntry{
            std::get<0>(state),
            std::get<1>(state),
            std::get<2>(state)
            };
    });

    // Bind JobShopEnvironment class
    nb::class_<JobShopEnvironment>(m, "JobShopEnvironment")
    .def(nb::init<std::vector<Job>>())
    .def("step", &JobShopEnvironment::step)
    .def("reset", &JobShopEnvironment::reset)
    .def("getState", &JobShopEnvironment::getState)
    .def("getPossibleActions", &JobShopEnvironment::getPossibleActions)
    .def("isDone", &JobShopEnvironment::isDone)
    .def("getTotalTime", &JobShopEnvironment::getTotalTime)
    .def("getJobs", &JobShopEnvironment::getJobs)
    .def("getNumMachines", &JobShopEnvironment::getNumMachines)
    .def("getScheduleData", &JobShopEnvironment::getScheduleData)
    .def("printSchedule", &JobShopEnvironment::printSchedule);

    // Bind JobShopAlgorithm abstract class
    nb::class_<JobShopAlgorithm>(m, "JobShopAlgorithm")
    .def("train", &JobShopAlgorithm::train)
    .def("printBestSchedule", &JobShopAlgorithm::printBestSchedule)
    .def("saveBestScheduleToFile", &JobShopAlgorithm::saveBestScheduleToFile);

    // Bind JobShopQLearning class
    nb::class_<JobShopQLearning, JobShopAlgorithm>(m, "JobShopQLearning")
    .def(nb::init<JobShopEnvironment&, double, double, double>())
    .def("runEpisode", &JobShopQLearning::runEpisode)
    .def("train", &JobShopQLearning::train)
    .def("printBestSchedule", &JobShopQLearning::printBestSchedule)
    .def("saveBestScheduleToFile", &JobShopQLearning::saveBestScheduleToFile)
    .def("applyAndPrintSchedule", &JobShopQLearning::applyAndPrintSchedule);

    // Bind JobShopActorCritic class
    nb::class_<JobShopActorCritic, JobShopAlgorithm>(m, "JobShopActorCritic")
    .def(nb::init<JobShopEnvironment&, double, double, double>())
    .def("runEpisode", &JobShopActorCritic::runEpisode)
    .def("train", &JobShopActorCritic::train)
    .def("printBestSchedule", &JobShopActorCritic::printBestSchedule)
    .def("saveBestScheduleToFile", &JobShopActorCritic::saveBestScheduleToFile)
    .def("applyAndPrintSchedule", &JobShopActorCritic::applyAndPrintSchedule);

    // Bind TaillardInstance enum
    nb::enum_<TaillardInstance>(m, "TaillardInstance")
    .value("TA01", TaillardInstance::TA01)
    .value("TA02", TaillardInstance::TA02)
    .value("TA03", TaillardInstance::TA03)
    .value("TA04", TaillardInstance::TA04)
    .value("TA05", TaillardInstance::TA05)
    .value("TA06", TaillardInstance::TA06)
    .value("TA07", TaillardInstance::TA07)
    .value("TA08", TaillardInstance::TA08)
    .value("TA09", TaillardInstance::TA09)
    .value("TA10", TaillardInstance::TA10)
    .value("TA11", TaillardInstance::TA11)
    .value("TA12", TaillardInstance::TA12)
    .value("TA13", TaillardInstance::TA13)
    .value("TA14", TaillardInstance::TA14)
    .value("TA15", TaillardInstance::TA15)
    .value("TA16", TaillardInstance::TA16)
    .value("TA17", TaillardInstance::TA17)
    .value("TA18", TaillardInstance::TA18)
    .value("TA19", TaillardInstance::TA19)
    .value("TA20", TaillardInstance::TA20)
    .value("TA21", TaillardInstance::TA21)
    .value("TA22", TaillardInstance::TA22)
    .value("TA23", TaillardInstance::TA23)
    .value("TA24", TaillardInstance::TA24)
    .value("TA25", TaillardInstance::TA25)
    .value("TA26", TaillardInstance::TA26)
    .value("TA27", TaillardInstance::TA27)
    .value("TA28", TaillardInstance::TA28)
    .value("TA29", TaillardInstance::TA29)
    .value("TA30", TaillardInstance::TA30)
    .value("TA31", TaillardInstance::TA31)
    .value("TA32", TaillardInstance::TA32)
    .value("TA33", TaillardInstance::TA33)
    .value("TA34", TaillardInstance::TA34)
    .value("TA35", TaillardInstance::TA35)
    .value("TA36", TaillardInstance::TA36)
    .value("TA37", TaillardInstance::TA37)
    .value("TA38", TaillardInstance::TA38)
    .value("TA39", TaillardInstance::TA39)
    .value("TA40", TaillardInstance::TA40)
    .value("TA41", TaillardInstance::TA41)
    .value("TA42", TaillardInstance::TA42)
    .value("TA43", TaillardInstance::TA43)
    .value("TA44", TaillardInstance::TA44)
    .value("TA45", TaillardInstance::TA45)
    .value("TA46", TaillardInstance::TA46)
    .value("TA47", TaillardInstance::TA47)
    .value("TA48", TaillardInstance::TA48)
    .value("TA49", TaillardInstance::TA49)
    .value("TA50", TaillardInstance::TA50)
    .value("TA51", TaillardInstance::TA51)
    .value("TA52", TaillardInstance::TA52)
    .value("TA53", TaillardInstance::TA53)
    .value("TA54", TaillardInstance::TA54)
    .value("TA55", TaillardInstance::TA55)
    .value("TA56", TaillardInstance::TA56)
    .value("TA57", TaillardInstance::TA57)
    .value("TA58", TaillardInstance::TA58)
    .value("TA59", TaillardInstance::TA59)
    .value("TA60", TaillardInstance::TA60)
    .value("TA61", TaillardInstance::TA61)
    .value("TA62", TaillardInstance::TA62)
    .value("TA63", TaillardInstance::TA63)
    .value("TA64", TaillardInstance::TA64)
    .value("TA65", TaillardInstance::TA65)
    .value("TA66", TaillardInstance::TA66)
    .value("TA67", TaillardInstance::TA67)
    .value("TA68", TaillardInstance::TA68)
    .value("TA69", TaillardInstance::TA69)
    .value("TA70", TaillardInstance::TA70)
    .value("TA71", TaillardInstance::TA71)
    .value("TA72", TaillardInstance::TA72)
    .value("TA73", TaillardInstance::TA73)
    .value("TA74", TaillardInstance::TA74)
    .value("TA75", TaillardInstance::TA75)
    .value("TA76", TaillardInstance::TA76)
    .value("TA77", TaillardInstance::TA77)
    .value("TA78", TaillardInstance::TA78)
    .value("TA79", TaillardInstance::TA79)
    .value("TA80", TaillardInstance::TA80);

    // Bind TaillardJobShopGenerator class
    nb::class_<TaillardJobShopGenerator>(m, "TaillardJobShopGenerator")
    .def_static("loadProblem", &TaillardJobShopGenerator::loadProblem)
    .def_static("verifyJobsData", &TaillardJobShopGenerator::verifyJobsData)
    .def_static("verifyOptimalSolution", &TaillardJobShopGenerator::verifyOptimalSolution)
    .def_static("runAllVerifications", &TaillardJobShopGenerator::runAllVerifications);

    nb::class_<LivePlotter>(m, "LivePlotter")
    .def(nb::init<int>())
    .def("render", &LivePlotter::render)
    .def("updateSchedule", &LivePlotter::updateSchedule)
    .def("shouldClose", &LivePlotter::shouldClose);
}