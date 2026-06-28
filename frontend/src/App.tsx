import { createBrowserRouter, RouterProvider } from "react-router-dom";
import { AppLayout } from "./components/AppLayout";
import { DashboardPage } from "./pages/DashboardPage";
import { DatasetDetailPage } from "./pages/DatasetDetailPage";
import { DatasetSnippetPage } from "./pages/DatasetSnippetPage";
import { DatasetsPage } from "./pages/DatasetsPage";
import { DetectorsPage } from "./pages/DetectorsPage";
import { RunDetailPage } from "./pages/RunDetailPage";
import { RunsPage } from "./pages/RunsPage";
import { SnippetPage } from "./pages/SnippetPage";

const router = createBrowserRouter([
  {
    path: "/",
    element: <AppLayout />,
    children: [
      { index: true, element: <DashboardPage /> },
      { path: "datasets", element: <DatasetsPage /> },
      { path: "datasets/:datasetId", element: <DatasetDetailPage /> },
      {
        path: "datasets/:datasetId/snippets/:snippetId",
        element: <DatasetSnippetPage />,
      },
      { path: "runs", element: <RunsPage /> },
      { path: "runs/:runId", element: <RunDetailPage /> },
      { path: "runs/:runId/snippets/:snippetId", element: <SnippetPage /> },
      { path: "detectors", element: <DetectorsPage /> },
    ],
  },
]);

export function App() {
  return <RouterProvider router={router} />;
}