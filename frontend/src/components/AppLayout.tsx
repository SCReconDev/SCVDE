import { NavLink, Outlet } from "react-router-dom";
import { Activity, Database, FlaskConical, LayoutDashboard } from "lucide-react";

export function AppLayout() {
  return (
    <div className="app-shell">
      <aside className="sidebar">
        <div className="brand">
          <div className="brand-icon">SC</div>

          <div>
            <div className="brand-title">SCVDE</div>
            <div className="brand-subtitle">
              Vulnerability Detection Evaluator
            </div>
          </div>
        </div>

        <nav className="nav">
          <NavLink to="/" end>
            <LayoutDashboard size={18} />
            Dashboard
          </NavLink>

          <NavLink to="/datasets">
            <Database size={18} />
            Datasets
          </NavLink>

          <NavLink to="/runs">
            <Activity size={18} />
            Runs
          </NavLink>

          <NavLink to="/detectors">
            <FlaskConical size={18} />
            Detectors
          </NavLink>
        </nav>
      </aside>

      <main className="main">
        <Outlet />
      </main>
    </div>
  );
}