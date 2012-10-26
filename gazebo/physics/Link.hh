/*
 * Copyright 2011 Nate Koenig
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
/* Desc: Link class
 * Author: Nate Koenig
 */

#ifndef _LINK_HH_
#define _LINK_HH_

#include <map>
#include <vector>
#include <string>

#include "common/Event.hh"
#include "common/CommonTypes.hh"

#include "physics/LinkState.hh"
#include "physics/Entity.hh"
#include "physics/Inertial.hh"
#include "physics/Joint.hh"

namespace gazebo
{
  namespace physics
  {
    class Model;
    class Collision;

    /// \addtogroup gazebo_physics
    /// \{

    /// \class Link Link.hh physics/physics.hh
    /// \brief Link class defines a rigid body entity, containing
    /// information on inertia, visual and collision properties of
    /// a rigid body.
    class Link : public Entity
    {
      /// \brief Constructor
      /// \param[in] _parent Parent of this link.
      public: explicit Link(EntityPtr _parent);

      /// \brief Destructor.
      public: virtual ~Link();

      /// \brief Load the body based on an SDF element.
      /// \param[in] _sdf SDF parameters.
      public: virtual void Load(sdf::ElementPtr _sdf);

      /// \brief Initialize the body.
      public: virtual void Init();

      /// \brief Finalize the body.
      public: void Fini();

      /// \brief Reset the link.
      public: void Reset();

      /// \brief Update the parameters using new sdf values.
      /// \param[in] _sdf SDF values to load from.
      public: virtual void UpdateParameters(sdf::ElementPtr _sdf);

      /// \brief Update the body.
      public: virtual void Update();

      /// \brief Set whether this body is enabled.
      /// \param[in] _enable True to enable the link in the physics engine.
      public: virtual void SetEnabled(bool _enable) const = 0;

      /// \brief Get whether this body is enabled in the physics engine.
      /// \return True if the link is enabled.
      public: virtual bool GetEnabled() const = 0;

      /// \brief Set whether this entity has been selected by the user
      /// through the gui
      /// \param[in] _set True to set the link as selected.
      public: virtual bool SetSelected(bool _set);

      /// \brief Set whether gravity affects this body.
      /// \param[in] _mode True to enable gravity.
      public: virtual void SetGravityMode(bool _mode) = 0;

      /// \brief Get the gravity mode.
      /// \return True if gravity is enabled.
      public: virtual bool GetGravityMode() = 0;

      /// \brief Set whether this body will collide with others in the
      /// model.
      /// \param[in] _collid True to enable collisions.
      public: virtual void SetSelfCollide(bool _collide) = 0;

      /// \TODO: reimplment this. Make collision mode an enum.
      /// \brief Set the collide mode of the body.
      /// \param[in] _mode Collision Mode.
      public: void SetCollideMode(const std::string &_mode);

      /// \brief Get Self-Collision Flag, if this is true, this body will
      /// collide with other bodies even if they share the same parent.
      /// \return True if self collision is enabled.
      public: bool GetSelfCollide();

      /// \brief Set the laser retro reflectiveness.
      /// \param[in] _retro Retro value for all child collisions.
      public: void SetLaserRetro(float _retro);

      /// \brief Set the linear velocity of the body.
      /// \param[in] _vel Linear velocity.
      public: virtual void SetLinearVel(const math::Vector3 &_vel) = 0;

      /// \brief Set the angular velocity of the body.
      /// \param[in] _vel Angular velocity.
      public: virtual void SetAngularVel(const math::Vector3 &_vel) = 0;

      /// \brief Set the linear acceleration of the body.
      /// \param[in] _accel Linear acceleration.
      public: void SetLinearAccel(const math::Vector3 &_accel);

      /// \brief Set the angular acceleration of the body.
      /// \param[in] _accel Angular acceleration.
      public: void SetAngularAccel(const math::Vector3 &_accel);

      /// \brief Set the force applied to the body.
      /// \param[in] _force Force value.
      public: virtual void SetForce(const math::Vector3 &_force) = 0;

      /// \brief Set the torque applied to the body.
      /// \param[in] _torque Torque value.
      public: virtual void SetTorque(const math::Vector3 &_torque) = 0;

      /// \brief Add a force to the body.
      /// \param[in] _force Force to add.
      public: virtual void AddForce(const math::Vector3 &_force) = 0;

      /// \brief Add a force to the body, components are relative to the
      /// body's own frame of reference.
      /// \param[in] _force Force to add.
      public: virtual void AddRelativeForce(const math::Vector3 &_force) = 0;

      /// \brief Add a force to the body using a global position.
      /// \param[in] _force Force to add.
      /// \param[in] _pos Position in global coord frame to add the force.
      public: virtual void AddForceAtWorldPosition(const math::Vector3 &_force,
                  const math::Vector3 &_pos) = 0;

      /// \brief Add a force to the body at position expressed to the body's
      /// own frame of reference.
      /// \param[in] _force Force to add.
      /// \param[in] _relPos Position on the link to add the force.
      public: virtual void AddForceAtRelativePosition(
                  const math::Vector3 &_force,
                  const math::Vector3 &_relPos) = 0;

      /// \brief Add a torque to the body.
      /// \param[in] _torque Torque value to add to the link.
      public: virtual void AddTorque(const math::Vector3 &_torque) = 0;

      /// \brief Add a torque to the body, components are relative to the
      /// body's own frame of reference.
      /// \param[in] _torque Torque value to add.
      public: virtual void AddRelativeTorque(const math::Vector3 &_torque) = 0;

      /// \brief Get the linear velocity of the body.
      /// \return Linear velocity of the body.
      public: math::Vector3 GetRelativeLinearVel() const;

      /// \brief Get the angular velocity of the body.
      /// \return Angular velocity of the body.
      public: math::Vector3 GetRelativeAngularVel() const;

      /// \brief Get the linear acceleration of the body.
      /// \return Linear acceleration of the body.
      public: math::Vector3 GetRelativeLinearAccel() const;

      /// \brief Get the linear acceleration of the body in the world frame.
      /// \return Linear acceleration of the body in the world frame.
      public: math::Vector3 GetWorldLinearAccel() const;

      /// \brief Get the angular acceleration of the body.
      /// \return Angular acceleration of the body.
      public: math::Vector3 GetRelativeAngularAccel() const;

      /// \brief Get the angular acceleration of the body in the world
      /// frame.
      /// \return Angular acceleration of the body in the world frame.
      public: math::Vector3 GetWorldAngularAccel() const;

      /// \brief Get the force applied to the body.
      /// \return Force applied to the body.
      public: math::Vector3 GetRelativeForce() const;

      /// \brief Get the force applied to the body in the world frame.
      /// \return Force applied to the body in the world frame.
      public: virtual math::Vector3 GetWorldForce() const = 0;

      /// \brief Get the torque applied to the body.
      /// \return Torque applied to the body.
      public: math::Vector3 GetRelativeTorque() const;

      /// \brief Get the torque applied to the body in the world frame.
      /// \return Torque applied to the body in the world frame.
      public: virtual math::Vector3 GetWorldTorque() const = 0;

      /// \brief Get the model that this body belongs to.
      /// \return Model that this body belongs to.
      public: ModelPtr GetModel() const;

      /// \brief Get the inertia of the link.
      /// \return Inertia of the link.
      public: InertialPtr GetInertial() const {return this->inertial;}

      /// \brief Set the mass of the link.
      /// \parma[in] _inertial Inertial value for the link.
      public: void SetInertial(const InertialPtr &_inertial);

      /// \brief Get a collision by id.
      /// \param[in] _id Id of the collision object to find.
      /// \return Pointer to the collision, NULL if the id is invalid.
      public: CollisionPtr GetCollisionById(unsigned int _id) const;

      /// \brief Get a child collision by name
      /// \param[in] _name Name of the collision object.
      /// \return Pointer to the collision, NULL if the name was not found.
      public: CollisionPtr GetCollision(const std::string &_name);

      /// \brief Get a child collision by index
      /// \param[in] _index Index of the collision object.
      /// \return Pointer to the collision, NULL if the name was not found.
      public: CollisionPtr GetCollision(unsigned int _index) const;

      /// \brief Get the bounding box for the link and all the child
      /// elements.
      /// \return The link's bounding box.
      public: virtual math::Box GetBoundingBox() const;

      /// \brief Set the linear damping factor.
      /// \param[in] _damping Linear damping factor.
      public: virtual void SetLinearDamping(double _damping) = 0;

      /// \brief Set the angular damping factor.
      /// \param[in] _damping Angular damping factor.
      public: virtual void SetAngularDamping(double _damping) = 0;

      /// \brief Get the linear damping factor.
      /// \return Linear damping.
      public: double GetLinearDamping() const;

      /// \brief Get the angular damping factor.
      /// \return Angular damping.
      public: double GetAngularDamping() const;

      /// \TODO Implement this function.
      /// \brief Set whether this body is in the kinematic state.
      /// \param[in] _kinematic True to make the link kinematic only.
      public: virtual void SetKinematic(const bool &_kinematic)

      /// \TODO Implement this function.
      /// \brief Get whether this body is in the kinematic state.
      /// \return True if the link is kinematic only.
      public: virtual bool GetKinematic() const {return false;}

      /// \brief Get sensor count
      ///
      /// This will return the number of sensors created by the link when it
      /// was loaded. This function is commonly used with
      /// Link::GetSensorName.
      /// \return The number of sensors created by the link.
      public: unsigned int GetSensorCount() const;

      /// \brief Get sensor name
      ///
      /// Get the name of a sensor based on an index. The index should be in
      /// the range of 0...Link::GetSensorCount().
      /// \note A Link does not manage or maintain a pointer to a
      /// sensors::Sensor. Access to a Sensor object
      /// is accomplished through the sensors::SensorManager. This was done to
      /// separate the physics engine from the sensor engine.
      /// \param[in] _index Index of the sensor name.
      /// \return The name of the sensor, or empty string if the index is out of
      /// bounds.
      public: std::string GetSensorName(unsigned int _index) const;

      /// \brief Connect to the add entity signal
      /// \param[in] _subscriber Subsciber callback function.
      /// \return Pointer to the connection, which must be kept in scope.
      public: template<typename T>
              event::ConnectionPtr ConnectEnabled(T _subscriber)
              {return enabledSignal.Connect(subscriber);}

      /// \brief Disconnect to the add entity signal.
      /// \param[in] _conn Connection pointer to disconnect.
      public: void DisconnectEnabled(event::ConnectionPtr &_conn)
              {enabledSignal.Disconnect(c);}

      /// \brief DEPRECATED
      public: void FillLinkMsg(msgs::Link &_msg) GAZEBO_DEPRECATED;

      /// \brief Fill a link message
      /// \param[out] _msg Message to fill
      public: void FillMsg(msgs::Link &_msg);

      /// \brief Update parameters from a message
      /// \param[in] _msg Message to read.
      public: void ProcessMsg(const msgs::Link &_msg);

      /// \brief Joints that have this Link as a parent Link.
      /// \param[in] _joint Joint that is a child of this link.
      public: void AddChildJoint(JointPtr _joint);

      /// \brief Joints that have this Link as a child Link.
      /// \param[in] _joint Joint that is a parent of this link.
      public: void AddParentJoint(JointPtr _joint);

      /// \brief Remove Joints that have this Link as a parent Link.
      /// \param[in] _joint Joint that is a child of this link.
      public: void RemoveChildJoint(JointPtr _joint);

      /// \brief Remove Joints that have this Link as a child Link
      /// \param[in] _joint Joint that is a parent of this link.
      public: void RemoveParentJoint(JointPtr _joint);

      /// \brief Attach a static model to this link
      /// \param[in] _model Pointer to a static model.
      /// \param[in] _offset Pose relative to this link to place the model.
      public: void AttachStaticModel(ModelPtr &_model,
                                     const math::Pose &_offset);

      /// \brief Detach a static model from this link.
      /// \param[in] _modelName Name of an attached model to detach.
      public: void DetachStaticModel(const std::string &_modelName);

      /// \brief Detach all static models from this link.
      public: void DetachAllStaticModels();

      /// \internal
      /// \brief Called when the pose is changed. Do not call this directly.
      public: virtual void OnPoseChange();

      /// \brief Get the link state.
      /// \return The state of this link.
      public: LinkState GetState();

      /// \brief Set the current link state.
      /// \param[in] _state The state to set the link to.
      public: void SetState(const LinkState &_state);

      /// \brief Update the mass matrix.
      public: virtual void UpdateMass() {}

      /// \brief Update surface parameters.
      public: virtual void UpdateSurface() {}

      /// \brief Allow the link to auto disable.
      /// \param[in] _disable If true, the link is allowed to auto disable.
      public: virtual void SetAutoDisable(bool _disable) = 0;

      /// \brief Returns a vector of children Links connected by joints.
      /// \return A vector of children Links connected by joints.
      public: Link_V GetChildJointsLinks() const;

      /// \brief Returns a vector of parent Links connected by joints.
      /// \return Vector of parent Links connected by joints.
      public: Link_V GetParentJointsLinks() const;

      /// \brief Load a new collision helper function.
      /// \param[in] _sdf SDF element used to load the collision.
      private: void LoadCollision(sdf::ElementPtr _sdf);

      /// \brief Set the inertial properties based on the collision
      /// entities.
      private: void SetInertialFromCollisions();

      /// \brief Inertial properties.
      protected: InertialPtr inertial;

      /// \brief Center of gravity visual elements.
      protected: std::vector<std::string> cgVisuals;

      /// \brief Link visual elements.
      protected: std::vector<std::string> visuals;

      /// \brief Linear acceleration.
      protected: math::Vector3 linearAccel;

      /// \brief Angular acceleration.
      protected: math::Vector3 angularAccel;

      /// \brief Offsets for the attached models.
      protected: std::vector<math::Pose> attachedModelsOffset;

      /// \brief Event used when the link is enabled or disabled.
      private: event::EventT<void (bool)> enabledSignal;

      /// \brief This flag is used to trigger the enabled
      private: bool enabled;

      /// \brief Names of all the sensors attached to the link.
      private: std::vector<std::string> sensors;

      /// \brief All the parent joints.
      private: std::vector<JointPtr> parentJoints;

      /// \brief All the child joints.
      private: std::vector<JointPtr> childJoints;

      /// \brief All the attached models.
      private: std::vector<ModelPtr> attachedModels;
    };
    /// \}
  }
}
#endif
