/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CANN_ASC_STL_ASC_STD___SET_SET_H
#define CANN_ASC_STL_ASC_STD___SET_SET_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::std {

#ifndef CANN_ASC_STL_DETAIL_ARENA_ASSOCIATIVE_SHARED
#define CANN_ASC_STL_DETAIL_ARENA_ASSOCIATIVE_SHARED
template <class First, class Second>
struct __arena_pair {
    First first;
    Second second;

    CANN_ASC_STL_API __arena_pair() = default;
    template <class Left, class Right>
    CANN_ASC_STL_API __arena_pair(Left&& left, Right&& right)
        : first(static_cast<Left&&>(left)), second(static_cast<Right&&>(right))
    {}
};

namespace __arena_associative_detail {

template <class Key>
struct identity_key {
    CANN_ASC_STL_API const Key& operator()(const Key& value) const noexcept
    {
        return value;
    }
};

template <class Key, class Mapped>
struct __arena_pair_key {
    CANN_ASC_STL_API const Key& operator()(const __arena_pair<const Key, Mapped>& value) const noexcept
    {
        return value.first;
    }
};
}  // namespace __arena_associative_detail
#endif

#ifndef CANN_ASC_STL_DETAIL_ARENA_TREE_IMPLEMENTATION
#define CANN_ASC_STL_DETAIL_ARENA_TREE_IMPLEMENTATION
namespace __arena_associative_detail {

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
class basic_tree {
    struct node {
        node* parent;
        node* left;
        node* right;
        int height;
        Value value;

        template <class Input>
        CANN_ASC_STL_API node(node* ancestor, Input&& input)
            : parent(ancestor), left(nullptr), right(nullptr), height(1), value(static_cast<Input&&>(input))
        {}
    };
    using node_allocator = typename Allocator::template rebind<node>::other;

public:
    using size_type = __SIZE_TYPE__;

    class iterator {
    public:
        CANN_ASC_STL_API iterator() = default;
        CANN_ASC_STL_API explicit iterator(node* current) : current_(current)
        {}
        CANN_ASC_STL_API Value& operator*() const
        {
            return current_->value;
        }
        CANN_ASC_STL_API Value* operator->() const
        {
            return &current_->value;
        }
        CANN_ASC_STL_API iterator& operator++()
        {
            if (current_->right != nullptr) {
                current_ = minimum(current_->right);
            } else {
                node* child = current_;
                current_ = current_->parent;
                while (current_ != nullptr && child == current_->right) {
                    child = current_;
                    current_ = current_->parent;
                }
            }
            return *this;
        }
        friend CANN_ASC_STL_API bool operator==(iterator left, iterator right)
        {
            return left.current_ == right.current_;
        }
        friend CANN_ASC_STL_API bool operator!=(iterator left, iterator right)
        {
            return !(left == right);
        }

    private:
        friend class basic_tree;
        CANN_ASC_STL_API static node* minimum(node* current)
        {
            while (current != nullptr && current->left != nullptr)
                current = current->left;
            return current;
        }
        node* current_ = nullptr;
    };

    CANN_ASC_STL_API basic_tree(const Compare& compare, const Allocator& allocator)
        : compare_(compare), allocator_(allocator)
    {}
    basic_tree(const basic_tree&) = delete;
    basic_tree& operator=(const basic_tree&) = delete;
    CANN_ASC_STL_API basic_tree(basic_tree&& other) noexcept
        : compare_(other.compare_), allocator_(other.allocator_), root_(other.root_), size_(other.size_)
    {
        other.root_ = nullptr;
        other.size_ = 0;
    }
    CANN_ASC_STL_API basic_tree& operator=(basic_tree&& other) noexcept
    {
        if (this != &other) {
            clear();
            compare_ = other.compare_;
            allocator_ = other.allocator_;
            root_ = other.root_;
            size_ = other.size_;
            other.root_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    CANN_ASC_STL_API ~basic_tree()
    {
        clear();
    }

    CANN_ASC_STL_API bool empty() const noexcept
    {
        return size_ == 0;
    }
    CANN_ASC_STL_API size_type size() const noexcept
    {
        return size_;
    }
    CANN_ASC_STL_API iterator begin() noexcept
    {
        return iterator(iterator::minimum(root_));
    }
    CANN_ASC_STL_API iterator end() noexcept
    {
        return iterator(nullptr);
    }

    template <class Input>
    CANN_ASC_STL_API __arena_pair<iterator, bool> insert(Input&& input)
    {
        const Key& key = key_of_(input);
        node* parent = nullptr;
        node** link = &root_;
        while (*link != nullptr) {
            parent = *link;
            const Key& current = key_of_(parent->value);
            if (compare_(key, current))
                link = &parent->left;
            else if (compare_(current, key))
                link = &parent->right;
            else
                return __arena_pair<iterator, bool>(iterator(parent), false);
        }
        node_allocator nodes(allocator_);
        node* created = nodes.allocate(1);
        ::new (static_cast<void*>(created)) node(parent, static_cast<Input&&>(input));
        *link = created;
        ++size_;
        rebalance_from(parent);
        return __arena_pair<iterator, bool>(iterator(created), true);
    }

    CANN_ASC_STL_API iterator find(const Key& key) noexcept
    {
        node* current = root_;
        while (current != nullptr) {
            const Key& current_key = key_of_(current->value);
            if (compare_(key, current_key))
                current = current->left;
            else if (compare_(current_key, key))
                current = current->right;
            else
                return iterator(current);
        }
        return end();
    }
    CANN_ASC_STL_API size_type count(const Key& key) noexcept
    {
        return find(key) == end() ? 0 : 1;
    }
    CANN_ASC_STL_API void clear() noexcept
    {
        node* stack[32];
        size_type used = 0;
        if (root_ != nullptr)
            stack[used++] = root_;
        node_allocator nodes(allocator_);
        while (used != 0) {
            node* current = stack[--used];
            if (current->left != nullptr)
                stack[used++] = current->left;
            if (current->right != nullptr)
                stack[used++] = current->right;
            current->~node();
            nodes.deallocate(current, 1);
        }
        root_ = nullptr;
        size_ = 0;
    }

private:
    CANN_ASC_STL_API static int height_of(node* current) noexcept
    {
        return current == nullptr ? 0 : current->height;
    }

    CANN_ASC_STL_API static void update_height(node* current) noexcept
    {
        const int left_height = height_of(current->left);
        const int right_height = height_of(current->right);
        current->height = 1 + (left_height < right_height ? right_height : left_height);
    }

    CANN_ASC_STL_API static int balance_of(node* current) noexcept
    {
        return height_of(current->left) - height_of(current->right);
    }

    CANN_ASC_STL_API void replace_parent_link(node* old_root, node* new_root) noexcept
    {
        node* parent = old_root->parent;
        new_root->parent = parent;
        if (parent == nullptr) {
            root_ = new_root;
        } else if (parent->left == old_root) {
            parent->left = new_root;
        } else {
            parent->right = new_root;
        }
    }

    CANN_ASC_STL_API node* rotate_left(node* old_root) noexcept
    {
        node* new_root = old_root->right;
        node* middle = new_root->left;
        replace_parent_link(old_root, new_root);
        new_root->left = old_root;
        old_root->parent = new_root;
        old_root->right = middle;
        if (middle != nullptr)
            middle->parent = old_root;
        update_height(old_root);
        update_height(new_root);
        return new_root;
    }

    CANN_ASC_STL_API node* rotate_right(node* old_root) noexcept
    {
        node* new_root = old_root->left;
        node* middle = new_root->right;
        replace_parent_link(old_root, new_root);
        new_root->right = old_root;
        old_root->parent = new_root;
        old_root->left = middle;
        if (middle != nullptr)
            middle->parent = old_root;
        update_height(old_root);
        update_height(new_root);
        return new_root;
    }

    CANN_ASC_STL_API node* rebalance(node* current) noexcept
    {
        update_height(current);
        const int balance = balance_of(current);
        if (balance > 1) {
            if (balance_of(current->left) < 0)
                rotate_left(current->left);
            return rotate_right(current);
        }
        if (balance < -1) {
            if (balance_of(current->right) > 0)
                rotate_right(current->right);
            return rotate_left(current);
        }
        return current;
    }

    CANN_ASC_STL_API void rebalance_from(node* current) noexcept
    {
        while (current != nullptr) {
            node* subtree_root = rebalance(current);
            current = subtree_root->parent;
        }
    }

    Compare compare_;
    Allocator allocator_;
    KeyOfValue key_of_{};
    node* root_ = nullptr;
    size_type size_ = 0;
};

}  // namespace __arena_associative_detail
#endif

template <class Key, class Compare, class Allocator>
class set {
    using tree_type = __arena_associative_detail::basic_tree<Key, Key, __arena_associative_detail::identity_key<Key>,
        Compare, Allocator>;

public:
    using value_type = Key;
    using size_type = __SIZE_TYPE__;
    using iterator = typename tree_type::iterator;
    CANN_ASC_STL_API explicit set(const Allocator& allocator) : tree_(Compare{}, allocator)
    {}
    CANN_ASC_STL_API set(const Compare& compare, const Allocator& allocator) : tree_(compare, allocator)
    {}
    set(const set&) = delete;
    set& operator=(const set&) = delete;
    CANN_ASC_STL_API set(set&&) noexcept = default;
    CANN_ASC_STL_API set& operator=(set&&) noexcept = default;
    CANN_ASC_STL_API bool empty() const noexcept
    {
        return tree_.empty();
    }
    CANN_ASC_STL_API size_type size() const noexcept
    {
        return tree_.size();
    }
    CANN_ASC_STL_API iterator begin() noexcept
    {
        return tree_.begin();
    }
    CANN_ASC_STL_API iterator end() noexcept
    {
        return tree_.end();
    }
    CANN_ASC_STL_API __arena_pair<iterator, bool> insert(const Key& key)
    {
        return tree_.insert(key);
    }
    CANN_ASC_STL_API __arena_pair<iterator, bool> insert(Key&& key)
    {
        return tree_.insert(static_cast<Key&&>(key));
    }
    CANN_ASC_STL_API iterator find(const Key& key) noexcept
    {
        return tree_.find(key);
    }
    CANN_ASC_STL_API size_type count(const Key& key) noexcept
    {
        return tree_.count(key);
    }
    CANN_ASC_STL_API void clear() noexcept
    {
        tree_.clear();
    }

private:
    tree_type tree_;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___SET_SET_H
